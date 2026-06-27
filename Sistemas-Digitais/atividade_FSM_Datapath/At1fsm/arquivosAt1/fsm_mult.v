// =============================================================
//  FSM de Controle — Multiplicação por Somas e Deslocamentos
//  Algoritmo: shift-and-add, LSB-first, 10 iterações
//
//  Mapeamento do banco de registradores:
//    R0 = operando A  (carregado externamente antes do inicio)
//    R1 = operando B  (carregado externamente antes do inicio)
//    R2 = acumulador  (resultado final)
//    R3 = cópia de B sendo deslocada para direita (>>)
//    R4 = constante 1 (máscara LSB e valor do incremento)
//    R5 = cópia de A sendo deslocada para esquerda (<<)
//    R6 = contador de iterações (0 até 10)
//    R7 = constante 10 (limite do loop)
//
//  Cada estado dura 1 pressionamento de KEY.
//  Total de pressionamentos: 7 (init) + ~55 (loop) ≈ 62 pressionamentos.
// =============================================================

module fsm_mult (
    input  wire        clk,       // Pulso do KEY (debounced)
    input  wire        rst,
    input  wire        inicio,    // SW[9]

    // Controle do datapath
    output reg         escreve,
    output reg  [2:0]  sel_ra,
    output reg  [2:0]  sel_rb,
    output reg  [2:0]  sel_rw,
    output reg  [2:0]  sel_op,
    output reg         mux_w_sel,
    output reg  [9:0]  ext_w,

    // Flags da ULA
    input  wire        z_flag,
    input  wire        c_flag,

    // Status
    output reg         pronto,
    output reg         overflow
);

    // ---------------------------------------------------------
    // Estados
    // ---------------------------------------------------------
    localparam [3:0]
        S_IDLE      = 4'd0,
        S_INIT_R2   = 4'd1,   // R2 = 0        (acumulador zerado)
        S_INIT_R3   = 4'd2,   // R3 = R1+R2    (cópia de B)
        S_INIT_R4   = 4'd3,   // R4 = 1        (constante)
        S_INIT_R5   = 4'd4,   // R5 = R0+R2    (cópia de A)
        S_INIT_R6   = 4'd5,   // R6 = 0        (contador)
        S_INIT_R7   = 4'd6,   // R7 = 10       (limite)
        S_CHECK     = 4'd7,   // R7-R6 == 0?   (fim do loop?)
        S_TEST_LSB  = 4'd8,   // R3 AND R4 == 0? (LSB de B = 0?)
        S_ADD       = 4'd9,   // R2 = R2 + R5
        S_SHIFT_A   = 4'd10,  // R5 = R5 << 1
        S_SHIFT_B   = 4'd11,  // R3 = R3 >> 1
        S_INC_CTR   = 4'd12,  // R6 = R6 + 1
        S_DONE      = 4'd13;  // pronto!

    reg [3:0] estado, prox_estado;
    reg       overflow_acc;

    // ---------------------------------------------------------
    // Registro de estado + captura de overflow
    // ---------------------------------------------------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            estado       <= S_IDLE;
            overflow_acc <= 1'b0;
        end else begin
            estado <= prox_estado;
            // Limpa overflow ao iniciar nova multiplicação
            if (prox_estado == S_INIT_R2)
                overflow_acc <= 1'b0;
            // Seta overflow se houver carry na soma parcial
            else if (estado == S_ADD && c_flag)
                overflow_acc <= 1'b1;
        end
    end

    // ---------------------------------------------------------
    // Próximo estado
    // ---------------------------------------------------------
    always @(*) begin
        case (estado)
            S_IDLE:     prox_estado = inicio ? S_INIT_R2  : S_IDLE;
            S_INIT_R2:  prox_estado = S_INIT_R3;
            S_INIT_R3:  prox_estado = S_INIT_R4;
            S_INIT_R4:  prox_estado = S_INIT_R5;
            S_INIT_R5:  prox_estado = S_INIT_R6;
            S_INIT_R6:  prox_estado = S_INIT_R7;
            S_INIT_R7:  prox_estado = S_CHECK;
            // z_flag=1 → R7-R6=0 → R6=10 → fim do loop
            S_CHECK:    prox_estado = z_flag ? S_DONE : S_TEST_LSB;
            // z_flag=1 → R3 AND 1 = 0 → LSB=0 → pula ADD
            S_TEST_LSB: prox_estado = z_flag ? S_SHIFT_A : S_ADD;
            S_ADD:      prox_estado = S_SHIFT_A;
            S_SHIFT_A:  prox_estado = S_SHIFT_B;
            S_SHIFT_B:  prox_estado = S_INC_CTR;
            S_INC_CTR:  prox_estado = S_CHECK;
            S_DONE:     prox_estado = inicio ? S_DONE : S_IDLE;
            default:    prox_estado = S_IDLE;
        endcase
    end

    // ---------------------------------------------------------
    // Saídas (Moore + Mealy nas transições de CHECK/TEST_LSB)
    // ---------------------------------------------------------
    always @(*) begin
        // Defaults
        escreve   = 1'b0;
        mux_w_sel = 1'b0;
        ext_w     = 10'd0;
        sel_ra    = 3'd0;
        sel_rb    = 3'd0;
        sel_rw    = 3'd0;
        sel_op    = 3'b011;
        pronto    = 1'b0;
        overflow  = overflow_acc;

        case (estado)
            // ----- Inicialização -----

            S_INIT_R2: begin
                // R2 = 0
                sel_rw    = 3'd2;
                ext_w     = 10'd0;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            S_INIT_R3: begin
                // R3 = R1 + R2 = R1 + 0 = R1  (cópia de B)
                sel_ra    = 3'd1;
                sel_rb    = 3'd2;
                sel_op    = 3'b011; // ADD
                sel_rw    = 3'd3;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_INIT_R4: begin
                // R4 = 1
                sel_rw    = 3'd4;
                ext_w     = 10'd1;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            S_INIT_R5: begin
                // R5 = R0 + R2 = R0 + 0 = R0  (cópia de A)
                sel_ra    = 3'd0;
                sel_rb    = 3'd2;
                sel_op    = 3'b011; // ADD
                sel_rw    = 3'd5;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_INIT_R6: begin
                // R6 = 0  (contador)
                sel_rw    = 3'd6;
                ext_w     = 10'd0;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            S_INIT_R7: begin
                // R7 = 10  (limite do loop)
                sel_rw    = 3'd7;
                ext_w     = 10'd10;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            // ----- Loop -----

            S_CHECK: begin
                // ULA: R7 - R6 → z_flag=1 quando R6=10 (fim)
                sel_ra = 3'd7;
                sel_rb = 3'd6;
                sel_op = 3'b110; // SUB
                // sem escrita
            end

            S_TEST_LSB: begin
                // ULA: R3 AND R4 → z_flag=1 quando LSB=0 (pula ADD)
                sel_ra = 3'd3;
                sel_rb = 3'd4;
                sel_op = 3'b100; // AND
                // sem escrita
            end

            S_ADD: begin
                // R2 = R2 + R5  (acumula A deslocado)
                sel_ra    = 3'd2;
                sel_rb    = 3'd5;
                sel_op    = 3'b011; // ADD
                sel_rw    = 3'd2;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_SHIFT_A: begin
                // R5 = R5 << 1  (desloca A para a próxima iteração)
                sel_ra    = 3'd5;
                sel_rb    = 3'd4; // R4=1 (quantidade do shift)
                sel_op    = 3'b001; // SLL
                sel_rw    = 3'd5;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_SHIFT_B: begin
                // R3 = R3 >> 1  (avança para o próximo bit de B)
                sel_ra    = 3'd3;
                sel_rb    = 3'd4; // R4=1
                sel_op    = 3'b010; // SRL
                sel_rw    = 3'd3;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_INC_CTR: begin
                // R6 = R6 + 1
                sel_ra    = 3'd6;
                sel_rb    = 3'd4; // R4=1
                sel_op    = 3'b011; // ADD
                sel_rw    = 3'd6;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_DONE: begin
                pronto   = 1'b1;
                overflow = overflow_acc;
                // sel_ra=2 → VA=R2 (resultado) visível no top-level
                sel_ra   = 3'd2;
                sel_rb   = 3'd0;
                sel_op   = 3'b011;
            end

            default: begin /* IDLE - nada */ end
        endcase
    end

endmodule
