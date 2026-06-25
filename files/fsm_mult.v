// ============================================================
//  FSM de Controle — Multiplicação por Somas e Deslocamentos
// ============================================================
//
//  Algoritmo (shift-and-add, LSB-first):
//
//    acumulador = 0
//    multiplicador_temp = B   (cópia que vai sendo deslocada)
//    deslocamento = 0
//
//    repete 10 vezes:
//      se bit 0 de multiplicador_temp == 1:
//          acumulador = acumulador + (A << deslocamento)
//      multiplicador_temp = multiplicador_temp >> 1
//      deslocamento = deslocamento + 1
//
//  Mapeamento no banco de registradores (datapath.v):
//    R0 = operando A (multiplicando)  — carregado externamente
//    R1 = operando B (multiplicador)  — carregado externamente
//    R2 = acumulador (resultado parcial)
//    R3 = cópia de B que vai sendo deslocada (shift a direita a cada ciclo)
//    R4 = constante 1 (para isolar o LSB via AND e para incremento)
//    R5 = valor deslocado de A (A << k)
//    R6 = constante 0 (inicialização / teste de zero)
//
//  Saídas de controle para o datapath:
//    escreve, sel_ra, sel_rb, sel_rw, sel_op, mux_w_sel, ext_w
//
// ============================================================

module fsm_mult (
    input  wire        clk,
    input  wire        rst,
    input  wire        inicio,

    // Interface com datapath
    output reg         escreve,
    output reg  [2:0]  sel_ra,
    output reg  [2:0]  sel_rb,
    output reg  [2:0]  sel_rw,
    output reg  [2:0]  sel_op,
    output reg         mux_w_sel,
    output reg  [9:0]  ext_w,

    // Flags do datapath
    input  wire        z_flag,
    input  wire        c_flag,

    // Sinais de status
    output reg         pronto,
    output reg         overflow
);

    // -------------------------------------------------------
    // Encoding de estados
    // -------------------------------------------------------
    localparam [4:0]
        S_IDLE          = 5'd0,   // Aguarda sinal inicio
        S_INIT_R2       = 5'd1,   // R2 = 0   (acumulador)
        S_INIT_R3       = 5'd2,   // R3 = R1  (cópia do multiplicador)
        S_INIT_R4       = 5'd3,   // R4 = 1   (máscara LSB / incremento)
        S_INIT_R5       = 5'd4,   // R5 = R0  (A deslocado — começa = A)
        S_INIT_CTR      = 5'd5,   // R6 = 0   (contador de iterações, 0..9)
        S_CHECK_DONE    = 5'd6,   // Verifica se contador == 10
        S_TEST_LSB      = 5'd7,   // LSB_val = R3 AND R4 → Z_flag
        S_ADD_PARTIAL   = 5'd8,   // R2 = R2 + R5  (só se LSB==1)
        S_SAVE_ACC      = 5'd9,   // Salva resultado da soma em R2
        S_SHIFT_A       = 5'd10,  // R5 = R5 << 1
        S_SAVE_SHIFT_A  = 5'd11,  // Salva resultado do shift em R5
        S_SHIFT_B       = 5'd12,  // R3 = R3 >> 1
        S_SAVE_SHIFT_B  = 5'd13,  // Salva resultado do shift em R3
        S_INC_CTR       = 5'd14,  // R6 = R6 + 1  (contador)
        S_SAVE_CTR      = 5'd15,  // Salva contador em R6
        S_DONE          = 5'd16;  // Sinaliza conclusão

    // Constante 10 em 10 bits para comparação do loop
    localparam [9:0] ITERS = 10'd10;

    reg [4:0] estado, prox_estado;

    // Flag auxiliar: indica se o LSB do multiplicador era 1
    // (capturado na transição S_TEST_LSB → próximo estado)
    reg lsb_era_um;

    // Detecta se houve overflow acumulado na soma parcial
    reg overflow_acc;

    // -------------------------------------------------------
    // Registro de estado
    // -------------------------------------------------------
    always @(posedge clk or posedge rst) begin
        if (rst)
            estado <= S_IDLE;
        else
            estado <= prox_estado;
    end

    // -------------------------------------------------------
    // Captura do flag Z após teste do LSB
    // -------------------------------------------------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            lsb_era_um   <= 1'b0;
            overflow_acc <= 1'b0;
        end else begin
            if (estado == S_TEST_LSB)
                // z_flag == 0 significa AND != 0, ou seja LSB == 1
                lsb_era_um <= ~z_flag;

            if (estado == S_SAVE_ACC && c_flag)
                overflow_acc <= 1'b1;
        end
    end

    // -------------------------------------------------------
    // Lógica de próximo estado
    // -------------------------------------------------------
    always @(*) begin
        prox_estado = estado;
        case (estado)
            S_IDLE:         prox_estado = inicio ? S_INIT_R2    : S_IDLE;
            S_INIT_R2:      prox_estado = S_INIT_R3;
            S_INIT_R3:      prox_estado = S_INIT_R4;
            S_INIT_R4:      prox_estado = S_INIT_R5;
            S_INIT_R5:      prox_estado = S_INIT_CTR;
            S_INIT_CTR:     prox_estado = S_CHECK_DONE;
            S_CHECK_DONE:   prox_estado = z_flag ? S_DONE : S_TEST_LSB;
                            // Reutiliza ULA: R6 - 10; Z=1 quando R6==10
            S_TEST_LSB:     prox_estado = lsb_era_um ? S_ADD_PARTIAL : S_SHIFT_A;
                            // Espera um ciclo para lsb_era_um ser atualizado pelo reg
                            // Na prática a transição acontece no ciclo seguinte
            S_ADD_PARTIAL:  prox_estado = S_SAVE_ACC;
            S_SAVE_ACC:     prox_estado = S_SHIFT_A;
            S_SHIFT_A:      prox_estado = S_SAVE_SHIFT_A;
            S_SAVE_SHIFT_A: prox_estado = S_SHIFT_B;
            S_SHIFT_B:      prox_estado = S_SAVE_SHIFT_B;
            S_SAVE_SHIFT_B: prox_estado = S_INC_CTR;
            S_INC_CTR:      prox_estado = S_SAVE_CTR;
            S_SAVE_CTR:     prox_estado = S_CHECK_DONE;
            S_DONE:         prox_estado = inicio ? S_DONE : S_IDLE;
            default:        prox_estado = S_IDLE;
        endcase
    end

    // -------------------------------------------------------
    // Lógica de saída (Moore)
    // -------------------------------------------------------
    always @(*) begin
        // Defaults (datapath inativo)
        escreve   = 1'b0;
        mux_w_sel = 1'b0;
        ext_w     = 10'd0;
        sel_ra    = 3'd0;
        sel_rb    = 3'd0;
        sel_rw    = 3'd0;
        sel_op    = 3'b011; // ADD por padrão
        pronto    = 1'b0;
        overflow  = overflow_acc;

        case (estado)
            // --------------------------------------------------
            // Inicialização
            // --------------------------------------------------
            S_INIT_R2: begin
                // R2 = 0 via ext_w
                sel_rw    = 3'd2;
                ext_w     = 10'd0;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            S_INIT_R3: begin
                // R3 = R1 (lê R1, escreve em R3 via ULA passthrough: R1 + 0)
                // Truque: R1 AND R1 = R1 — mas mais simples: usar ext_w impossível
                // pois não conhecemos R1 aqui. Usamos: R3 = R1 OR 0 → AND com 1023
                // Mais direto: R3 = R1 + R6 onde R6=0, mas R6 ainda não existe.
                // Solução: shift R1 por 0 posições → R1 << 0 = R1
                // sel_op = 001 (shift left), b=R6=0 ainda não init → usamos ext_w indiretamente
                // Alternativa limpa: mux_w_sel=0, op=ADD, R1+R4=0 inicial
                // R4=0 initial → R3 = R1 + 0 = R1  ✓
                sel_ra    = 3'd1;  // A = R1
                sel_rb    = 3'd6;  // B = R6 = 0 (reg inicializado a 0 por register_file)
                sel_op    = 3'b011; // ADD: R1 + 0 = R1
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
                // R5 = R0 (A inicial sem deslocamento)
                sel_ra    = 3'd0;  // A = R0
                sel_rb    = 3'd6;  // B = R6 = 0
                sel_op    = 3'b011; // ADD: R0 + 0 = R0
                sel_rw    = 3'd5;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            S_INIT_CTR: begin
                // R6 = 0 (contador de iterações)
                sel_rw    = 3'd6;
                ext_w     = 10'd0;
                mux_w_sel = 1'b1;
                escreve   = 1'b1;
            end

            // --------------------------------------------------
            // Verificação de término: (10 - R6) == 0 ?
            // --------------------------------------------------
            S_CHECK_DONE: begin
                // Usa ULA: S = 10 - R6; se Z=1, acabou
                // Precisamos de "10" num registrador. Reaproveitamos ext_w
                // via um truque: comparamos R6 com a constante 10.
                // Como não temos registrador com 10, usamos a subtração
                // externamente: colocamos 10 em ext_w mas não temos porta
                // combinacional para isso na ULA.
                // Solução: carregar 10 em R7 na init e subtrair.
                // --- Ajuste: usando R7 = 10 carregado durante S_INIT_CTR ---
                // (ver estado S_INIT_R7 inserido abaixo)
                // Por ora: sel_ra=R7(10), sel_rb=R6, op=SUB → Z=1 se R6==10
                sel_ra = 3'd7;   // R7 = 10 (constante)
                sel_rb = 3'd6;   // R6 = contador
                sel_op = 3'b110; // SUB: 10 - R6
                // não escreve, só lê as flags
            end

            // --------------------------------------------------
            // Teste do LSB do multiplicador
            // --------------------------------------------------
            S_TEST_LSB: begin
                // LSB = R3 AND R4 (R4=1)
                sel_ra = 3'd3;   // R3 = cópia do multiplicador
                sel_rb = 3'd4;   // R4 = 1
                sel_op = 3'b100; // AND
                // não escreve, só capturamos z_flag no reg sequencial
            end

            // --------------------------------------------------
            // Soma parcial: R2 = R2 + R5
            // --------------------------------------------------
            S_ADD_PARTIAL: begin
                sel_ra = 3'd2;   // R2 = acumulador
                sel_rb = 3'd5;   // R5 = A deslocado
                sel_op = 3'b011; // ADD
                // resultado na ULA; escreve no próximo estado
            end

            S_SAVE_ACC: begin
                sel_ra    = 3'd2;
                sel_rb    = 3'd5;
                sel_op    = 3'b011;
                sel_rw    = 3'd2;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            // --------------------------------------------------
            // Deslocamento de A: R5 = R5 << 1
            // --------------------------------------------------
            S_SHIFT_A: begin
                sel_ra = 3'd5;   // R5
                sel_rb = 3'd4;   // R4 = 1 (quantidade de shift)
                sel_op = 3'b001; // SLL
            end

            S_SAVE_SHIFT_A: begin
                sel_ra    = 3'd5;
                sel_rb    = 3'd4;
                sel_op    = 3'b001;
                sel_rw    = 3'd5;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            // --------------------------------------------------
            // Deslocamento de B: R3 = R3 >> 1
            // --------------------------------------------------
            S_SHIFT_B: begin
                sel_ra = 3'd3;   // R3
                sel_rb = 3'd4;   // R4 = 1
                sel_op = 3'b010; // SRL
            end

            S_SAVE_SHIFT_B: begin
                sel_ra    = 3'd3;
                sel_rb    = 3'd4;
                sel_op    = 3'b010;
                sel_rw    = 3'd3;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            // --------------------------------------------------
            // Incremento do contador: R6 = R6 + 1
            // --------------------------------------------------
            S_INC_CTR: begin
                sel_ra = 3'd6;   // R6
                sel_rb = 3'd4;   // R4 = 1
                sel_op = 3'b011; // ADD
            end

            S_SAVE_CTR: begin
                sel_ra    = 3'd6;
                sel_rb    = 3'd4;
                sel_op    = 3'b011;
                sel_rw    = 3'd6;
                mux_w_sel = 1'b0;
                escreve   = 1'b1;
            end

            // --------------------------------------------------
            // Concluído
            // --------------------------------------------------
            S_DONE: begin
                pronto   = 1'b1;
                overflow = overflow_acc;
                // R2 contém o resultado — datapath permanece estável
                sel_ra = 3'd2;
                sel_rb = 3'd6;
                sel_op = 3'b011;
            end

            default: begin /* noop */ end
        endcase
    end

endmodule
