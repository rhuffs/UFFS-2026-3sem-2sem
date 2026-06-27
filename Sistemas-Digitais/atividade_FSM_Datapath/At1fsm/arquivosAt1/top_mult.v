// =============================================================
//  Top-Level — Multiplicador FSM + Datapath
//  Plataforma: Altera DE1 (Cyclone II EP2C20F484C7)
//
//  ── Como usar ─────────────────────────────────────────────
//
//  PASSO 1 — Carregar operando A (SW[9]=0, SW[8]=0):
//    Coloca o valor de A em SW[7:0]
//    Pressiona KEY[0] uma vez → A gravado em R0
//
//  PASSO 2 — Carregar operando B (SW[9]=0, SW[8]=1):
//    Coloca o valor de B em SW[7:0]
//    Pressiona KEY[0] uma vez → B gravado em R1
//
//  PASSO 3 — Multiplicar (SW[9]=1):
//    Vira SW[9] para cima
//    Pressiona KEY[0] repetidamente (~62 vezes)
//    LEDR[9] acende quando termina
//    Resultado aparece em HEX3-HEX0 em decimal
//    LEDR[8] acende se overflow (resultado > 1023)
//
//  Reset: KEY[1] a qualquer momento
// =============================================================

module top_mult (
    input  wire        CLOCK_50,
    input  wire [3:0]  KEY,     // ativo-baixo; [0]=clock FSM, [1]=reset
    input  wire [9:0]  SW,      // [9]=inicio, [8]=sel_op, [7:0]=valor
    output wire [9:0]  LEDR,
    output wire [7:0]  LEDG,
    output wire [6:0]  HEX0,
    output wire [6:0]  HEX1,
    output wire [6:0]  HEX2,
    output wire [6:0]  HEX3
);

    // ---------------------------------------------------------
    // Reset e clock da FSM
    // ---------------------------------------------------------
    wire rst = ~KEY[1];
    wire clk_pulso;

    debounce u_deb (
        .clk_sys (CLOCK_50),
        .rst     (rst),
        .btn_n   (KEY[0]),
        .pulso   (clk_pulso)
    );

    // ---------------------------------------------------------
    // Modo de operação
    // SW[9]=0 → carga de operandos
    // SW[9]=1 → executa multiplicação
    // ---------------------------------------------------------
    wire modo_carga = ~SW[9];
    wire inicio     =  SW[9];

    // ---------------------------------------------------------
    // Sinais da FSM
    // ---------------------------------------------------------
    wire        escreve_fsm;
    wire [2:0]  sel_ra_fsm, sel_rb_fsm, sel_rw_fsm, sel_op_fsm;
    wire        mux_w_sel_fsm;
    wire [9:0]  ext_w_fsm;
    wire        pronto, overflow_fsm;

    // ---------------------------------------------------------
    // Controle no modo carga
    // SW[8]=0 → escreve em R0 (operando A)
    // SW[8]=1 → escreve em R1 (operando B)
    // ---------------------------------------------------------
    wire [2:0] sel_rw_ld  = SW[8] ? 3'd1 : 3'd0;
    wire [9:0] ext_w_ld   = {2'b00, SW[7:0]};
    wire       escreve_ld = clk_pulso & modo_carga;

    // ---------------------------------------------------------
    // MUX: carga ou FSM
    // ---------------------------------------------------------
    wire        escreve_dp   = modo_carga ? escreve_ld    : escreve_fsm;
    wire [2:0]  sel_ra_dp    = modo_carga ? 3'd0          : sel_ra_fsm;
    wire [2:0]  sel_rb_dp    = modo_carga ? 3'd0          : sel_rb_fsm;
    wire [2:0]  sel_rw_dp    = modo_carga ? sel_rw_ld     : sel_rw_fsm;
    wire [2:0]  sel_op_dp    = modo_carga ? 3'b011        : sel_op_fsm;
    wire        mux_w_sel_dp = modo_carga ? 1'b1          : mux_w_sel_fsm;
    wire [9:0]  ext_w_dp     = modo_carga ? ext_w_ld      : ext_w_fsm;

    // ---------------------------------------------------------
    // Datapath
    // ---------------------------------------------------------
    wire [9:0] va, vb, s_ula;
    wire       z_flag, c_flag;

    datapath u_dp (
        .clk       (CLOCK_50),
        .escreve   (escreve_dp),
        .sel_ra    (sel_ra_dp),
        .sel_rb    (sel_rb_dp),
        .sel_rw    (sel_rw_dp),
        .sel_op    (sel_op_dp),
        .mux_w_sel (mux_w_sel_dp),
        .ext_w     (ext_w_dp),
        .va        (va),
        .vb        (vb),
        .s         (s_ula),
        .z         (z_flag),
        .c         (c_flag)
    );

    // ---------------------------------------------------------
    // FSM (resetada enquanto em modo carga)
    // ---------------------------------------------------------
    fsm_mult u_fsm (
        .clk       (clk_pulso),
        .rst       (rst | modo_carga),
        .inicio    (inicio),
        .escreve   (escreve_fsm),
        .sel_ra    (sel_ra_fsm),
        .sel_rb    (sel_rb_fsm),
        .sel_rw    (sel_rw_fsm),
        .sel_op    (sel_op_fsm),
        .mux_w_sel (mux_w_sel_fsm),
        .ext_w     (ext_w_fsm),
        .z_flag    (z_flag),
        .c_flag    (c_flag),
        .pronto    (pronto),
        .overflow  (overflow_fsm)
    );

    // ---------------------------------------------------------
    // Resultado: quando FSM está em DONE, sel_ra=2 → VA = R2
    // ---------------------------------------------------------
    wire [9:0] resultado = va;

    // ---------------------------------------------------------
    // Binário → BCD → Displays
    // ---------------------------------------------------------
    wire [3:0] d0, d1, d2, d3;

    bin2bcd u_bcd (
        .bin (resultado),
        .d0  (d0), .d1 (d1),
        .d2  (d2), .d3 (d3)
    );

    bcd_7seg u_h0 (.bcd(d0), .seg(HEX0));
    bcd_7seg u_h1 (.bcd(d1), .seg(HEX1));
    bcd_7seg u_h2 (.bcd(d2), .seg(HEX2));
    bcd_7seg u_h3 (.bcd(d3), .seg(HEX3));

    // ---------------------------------------------------------
    // LEDs
    // LEDR[9] = pronto
    // LEDR[8] = overflow
    // LEDR[7:0] = bits do resultado (debug)
    // ---------------------------------------------------------
    assign LEDR[9]   = pronto;
    assign LEDR[8]   = overflow_fsm;
    assign LEDR[7:0] = resultado[7:0];

    assign LEDG = 8'b0;

endmodule
