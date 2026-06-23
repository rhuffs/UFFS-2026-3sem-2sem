// Datapath Top-Level
// Integra: Banco de Registradores + MUX_W + ULA
//
// Estrutura:
//   VA ──────────────────► A ──► ULA ──► S / Z / C
//   VB ──────────────────► B
//
//   MUX_W seleciona o valor a escrever no banco: saída da ULA (S) ou entrada externa (ext_w).

//`include "register_file.v"
//`include "ula.v"

module datapath (
    input  wire        clk,
    input  wire        escreve,       // Habilita escrita no banco de registradores

    // Seleções do banco de registradores
    input  wire [2:0]  sel_ra,
    input  wire [2:0]  sel_rb,
    input  wire [2:0]  sel_rw,

    // Seleção de operação da ULA
    input  wire [2:0]  sel_op,

    // Controle do MUX de escrita
    input  wire        mux_w_sel,    // 0 = S (ULA), 1 = ext_w

    // Entrada externa para escrita direta no banco
    input  wire [9:0]  ext_w,

    // Saídas observáveis
    output wire [9:0]  va,           // Saída A do banco
    output wire [9:0]  vb,           // Saída B do banco
    output wire [9:0]  s,            // Resultado da ULA
    output wire        z,            // Flag zero
    output wire        c             // Flag carry/borrow/overflow
);

    // ----------------------------------------------------------------
    // Fios internos
    // ----------------------------------------------------------------
    wire [9:0] vw;

    // ----------------------------------------------------------------
    // Banco de Registradores
    // ----------------------------------------------------------------
    register_file rf (
        .clk     (clk),
        .escreve (escreve),
        .sel_ra  (sel_ra),
        .sel_rb  (sel_rb),
        .sel_rw  (sel_rw),
        .vw      (vw),
        .va      (va),
        .vb      (vb)
    );

    // ----------------------------------------------------------------
    // ULA — entradas diretas do banco de registradores
    // ----------------------------------------------------------------
    ula alu (
        .a      (va),
        .b      (vb),
        .sel_op (sel_op),
        .s      (s),
        .z      (z),
        .c      (c)
    );

    // ----------------------------------------------------------------
    // MUX W — seleciona valor a escrever no banco
    // ----------------------------------------------------------------
    assign vw = mux_w_sel ? ext_w : s;

endmodule

// Banco de Registradores: 8 registradores de 10 bits
module register_file (
    input  wire        clk,
    input  wire        escreve,       // Escrita na borda de subida
    input  wire [2:0]  sel_ra,        // Seleção do registrador A (leitura)
    input  wire [2:0]  sel_rb,        // Seleção do registrador B (leitura)
    input  wire [2:0]  sel_rw,        // Seleção do registrador a escrever
    input  wire [9:0]  vw,            // Valor a escrever
    output wire [9:0]  va,            // Saída do registrador A
    output wire [9:0]  vb             // Saída do registrador B
);

    reg [9:0] regs [0:7];   // 8 registradores de 10 bits

    integer i;
    initial begin
        for (i = 0; i < 8; i = i + 1)
            regs[i] = 10'd0;
    end

    // Escrita síncrona na borda de subida de 'escreve'
    always @(posedge escreve) begin
        regs[sel_rw] <= vw;
    end

    // Leitura combinacional
    assign va = regs[sel_ra];
    assign vb = regs[sel_rb];

endmodule

// Unidade Lógica Aritmética (ULA) - 10 bits
// SelOp | Operação
//  000  | A * B
//  001  | A << B
//  010  | A >> B
//  011  | A + B
//  100  | A AND B
//  101  | A / B
//  110  | A - B
//  111  | A XOR B
module ula (
    input  wire [9:0]  a,
    input  wire [9:0]  b,
    input  wire [2:0]  sel_op,
    output reg  [9:0]  s,     // Resultado
    output reg         z,     // Zero flag
    output reg         c      // Overflow/Underflow flag (Carry/Borrow)
);

    // Registradores intermediários de largura extra para detectar overflow
    reg [19:0] result_mul;
    reg [10:0] result_wide;   // 11 bits para capturar carry/borrow

    always @(*) begin
        c = 1'b0;
        z = 1'b0;

        case (sel_op)
            3'b000: begin // A * B (multiplicação — resultado truncado para 10 bits)
                result_mul = a * b;
                s = result_mul[9:0];
                c = |result_mul[19:10];  // Overflow se bits superiores != 0
            end

            3'b001: begin // A << B (shift lógico à esquerda)
                result_wide = {1'b0, a} << b;
                s = result_wide[9:0];
                c = result_wide[10];     // Bit deslocado para fora
            end

            3'b010: begin // A >> B (shift lógico à direita)
                s = a >> b;
                // Carry: último bit deslocado para fora (se b > 0)
                c = (b > 0) ? a[b-1] : 1'b0;
            end

            3'b011: begin // A + B (adição)
                result_wide = {1'b0, a} + {1'b0, b};
                s = result_wide[9:0];
                c = result_wide[10];     // Carry out
            end

            3'b100: begin // A AND B
                s = a & b;
                c = 1'b0;
            end

            3'b101: begin // A / B (divisão inteira)
                if (b == 10'd0) begin
                    s = 10'hXX;          // Divisão por zero — resultado indefinido
                    c = 1'b1;
                end else begin
                    s = a / b;
                    c = 1'b0;
                end
            end

            3'b110: begin // A - B (subtração)
                result_wide = {1'b0, a} - {1'b0, b};
                s = result_wide[9:0];
                c = result_wide[10];     // Borrow (underflow)
            end

            3'b111: begin // A XOR B
                s = a ^ b;
                c = 1'b0;
            end

            default: begin
                s = 10'd0;
                c = 1'b0;
            end
        endcase

        z = (s == 10'd0) ? 1'b1 : 1'b0;
    end

endmodule

module fsm_polinomio (
    input  wire        clk,
    input  wire        reset,
    input  wire        inicio,
    input  wire        z,
    input  wire        c,
    output reg         escreve,
    output reg  [2:0]  sel_ra,
    output reg  [2:0]  sel_rb,
    output reg  [2:0]  sel_rw,
    output reg  [2:0]  sel_op,
    output reg         mux_w_sel,
    output reg         overflow_led
);

    parameter S0_IDLE     = 4'd0,
              S1_CALC_D1  = 4'd1,
              S2_CALC_D2  = 4'd2,
              S3_RST_CNT  = 4'd3,
              S4_VERIFICA = 4'd4,
              S5_PROX_P   = 4'd5,
              S6_PROX_D1  = 4'd6,
              S7_INC_CNT  = 4'd7,
              S8_FIM      = 4'd8;

    reg [3:0] estado_atual, proximo_estado;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            estado_atual <= S0_IDLE;
            overflow_led <= 1'b0;
        end else begin
            estado_atual <= proximo_estado;
            if ((estado_atual == S5_PROX_P || estado_atual == S6_PROX_D1) && c) begin
                overflow_led <= 1'b1;
            end
        end
    end

    always @(*) begin
        escreve   = 1'b0;
        sel_ra    = 3'd0;
        sel_rb    = 3'd0;
        sel_rw    = 3'd0;
        sel_op    = 3'b000;
        mux_w_sel = 1'b0;
        proximo_estado = estado_atual;

        case (estado_atual)
            S0_IDLE: begin
                escreve = 1'b1;
                sel_rw  = 3'd6;
                mux_w_sel = 1'b1;
                if (inicio)
                    proximo_estado = S1_CALC_D1;
            end

            S1_CALC_D1: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd1;
                sel_rw  = 3'd3;
                sel_op  = 3'b011;
                proximo_estado = S2_CALC_D2;
            end

            S2_CALC_D2: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd0;
                sel_rw  = 3'd4;
                sel_op  = 3'b011;
                proximo_estado = S3_RST_CNT;
            end

            S3_RST_CNT: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd0;
                sel_rw  = 3'd5;
                sel_op  = 3'b111;
                proximo_estado = S4_VERIFICA;
            end

            S4_VERIFICA: begin
                escreve = 1'b0;
                sel_ra  = 3'd6;
                sel_rb  = 3'd5;
                sel_op  = 3'b110;
                sel_ra  = (z) ? 3'd2 : 3'd6; 
                if (z) proximo_estado = S8_FIM;
                else   proximo_estado = S5_PROX_P;
            end

            S5_PROX_P: begin
                escreve = 1'b1;
                sel_ra  = 3'd2;
                sel_rb  = 3'd3;
                sel_rw  = 3'd2;
                sel_op  = 3'b011;
                proximo_estado = S6_PROX_D1;
            end

            S6_PROX_D1: begin
                escreve = 1'b1;
                sel_ra  = 3'd3;
                sel_rb  = 3'd4;
                sel_rw  = 3'd3;
                sel_op  = 3'b011;
                proximo_estado = S7_INC_CNT;
            end

            S7_INC_CNT: begin
                escreve = 1'b1;
                sel_ra  = 3'd5;
                sel_rb  = 3'd7;
                sel_rw  = 3'd5;
                sel_op  = 3'b011;
                proximo_estado = S4_VERIFICA;
            end

            S8_FIM: begin
                escreve = 1'b0;
                sel_ra  = 3'd2;
                proximo_estado = S8_FIM;
            end
            
            default: proximo_estado = S0_IDLE;
        endcase
    end
endmodule

module top_polinomio (
    input  wire        CLOCK_50,
    input  wire [3:0]  KEY,
    input  wire [9:0]  SW,
    output wire [9:0]  LEDR,
    output wire [6:0]  HEX0,
    output wire [6:0]  HEX1,
    output wire [6:0]  HEX2,
    output wire [6:0]  HEX3
);

    wire       escreve;
    wire [2:0] sel_ra, sel_rb, sel_rw, sel_op;
    wire       mux_w_sel;
    wire [9:0] va_out, vb_out, s_out;
    wire       ula_z, ula_c;

    wire clk_fsm   = ~KEY[0]; 
    wire rst_fsm   = ~KEY[3];
    wire start_fsm = ~KEY[1];

    fsm_polinomio fsm_inst (
        .clk          (clk_fsm),
        .reset        (rst_fsm),
        .inicio       (start_fsm),
        .z            (ula_z),
        .c            (ula_c),
        .escreve      (escreve),
        .sel_ra       (sel_ra),
        .sel_rb       (sel_rb),
        .sel_rw       (sel_rw),
        .sel_op       (sel_op),
        .mux_w_sel    (mux_w_sel),
        .overflow_led (LEDR[0])
    );

    datapath dp_inst (
        .clk       (clk_fsm),
        .escreve   (escreve),
        .sel_ra    (sel_ra),
        .sel_rb    (sel_rb),
        .sel_rw    (sel_rw),
        .sel_op    (sel_op),
        .mux_w_sel (mux_w_sel),
        .ext_w     (SW),
        .va        (va_out),
        .vb        (vb_out),
        .s         (s_out),
        .z         (ula_z),
        .c         (ula_c)
    );

    assign LEDR[9:1] = 9'b000000000;

    wire [3:0] digito_milhar  = va_out / 1000;
    wire [3:0] digito_centena = (va_out % 1000) / 100;
    wire [3:0] digito_dezena  = (va_out % 100) / 10;
    wire [3:0] digito_unidade = va_out % 10;

    function [6:0] bcd_to_7seg;
        input [3:0] bcd;
        case (bcd)
            4'd0: bcd_to_7seg = 7'b1000000;
            4'd1: bcd_to_7seg = 7'b1111001;
            4'd2: bcd_to_7seg = 7'b0100100;
            4'd3: bcd_to_7seg = 7'b0110000;
            4'd4: bcd_to_7seg = 7'b0011001;
            4'd5: bcd_to_7seg = 7'b0010010;
            4'd6: bcd_to_7seg = 7'b0000010;
            4'd7: bcd_to_7seg = 7'b1111000;
            4'd8: bcd_to_7seg = 7'b0000000;
            4'd9: bcd_to_7seg = 7'b0010000;
            default: bcd_to_7seg = 7'b1111111;
        endcase
    endfunction

    assign HEX0 = bcd_to_7seg(digito_unidade);
    assign HEX1 = bcd_to_7seg(digito_dezena);
    assign HEX2 = bcd_to_7seg(digito_centena);
    assign HEX3 = bcd_to_7seg(digito_milhar);

endmodule