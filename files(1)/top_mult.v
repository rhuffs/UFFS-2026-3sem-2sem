// ============================================================
//  Top-Level — Multiplicação FSM + Datapath
//  Plataforma: Altera DE1 (Cyclone II EP2C20F484C7)
//  Quartus 13.0 ou superior
//
//  ── Pinagem ───────────────────────────────────────────────
//    CLOCK_50   : PIN_L1  — clock 50 MHz
//    KEY[0]     : PIN_R22 — clock manual da FSM (ativo-baixo)
//    KEY[1]     : PIN_R21 — reset geral         (ativo-baixo)
//    SW[9]      : PIN_L2  — 0=modo carga / 1=inicia multiplicação
//    SW[8]      : PIN_M1  — seleciona operando: 0=A(R0) / 1=B(R1)
//    SW[7:0]    : valor a carregar (8 bits)
//
//  ── Saídas ────────────────────────────────────────────────
//    HEX3–HEX0 : resultado em decimal (ativo-baixo)
//    LEDR[9]   : pronto
//    LEDR[8]   : overflow (resultado > 1023)
//    LEDR[7:0] : bits [7:0] do resultado (debug)
//    LEDG[7:0] : bits do estado da FSM (debug, opcional)
// ============================================================

module top_mult (
    input  wire        CLOCK_50,
    input  wire [3:0]  KEY,       // ativo-baixo
    input  wire [9:0]  SW,
    output wire [9:0]  LEDR,
    output wire [7:0]  LEDG,
    output wire [6:0]  HEX0,
    output wire [6:0]  HEX1,
    output wire [6:0]  HEX2,
    output wire [6:0]  HEX3
);

    // -------------------------------------------------------
    // Reset e clock da FSM com debounce
    // -------------------------------------------------------
    wire rst      = ~KEY[1];
    wire clk_pulso;

    debounce u_deb (
        .clk_sys (CLOCK_50),
        .rst     (rst),
        .btn_n   (KEY[0]),
        .pulso   (clk_pulso)
    );

    // -------------------------------------------------------
    // Modo carga (SW[9]=0) vs. multiplicação (SW[9]=1)
    // -------------------------------------------------------
    wire modo_carga = ~SW[9];
    wire inicio     =  SW[9];

    // -------------------------------------------------------
    // Sinais FSM → datapath
    // -------------------------------------------------------
    wire        escreve_fsm;
    wire [2:0]  sel_ra_fsm, sel_rb_fsm, sel_rw_fsm, sel_op_fsm;
    wire        mux_w_sel_fsm;
    wire [9:0]  ext_w_fsm;

    // -------------------------------------------------------
    // Controle no modo carga
    // -------------------------------------------------------
    wire [2:0]  sel_rw_ld  = SW[8] ? 3'd1 : 3'd0;   // R0=A / R1=B
    wire [9:0]  ext_w_ld   = {2'b00, SW[7:0]};
    wire        escreve_ld = clk_pulso & modo_carga;

    // MUX de controle
    wire        escreve_dp   = modo_carga ? escreve_ld    : escreve_fsm;
    wire [2:0]  sel_ra_dp    = modo_carga ? 3'd0          : sel_ra_fsm;
    wire [2:0]  sel_rb_dp    = modo_carga ? 3'd0          : sel_rb_fsm;
    wire [2:0]  sel_rw_dp    = modo_carga ? sel_rw_ld     : sel_rw_fsm;
    wire [2:0]  sel_op_dp    = modo_carga ? 3'b011        : sel_op_fsm;
    wire        mux_w_sel_dp = modo_carga ? 1'b1          : mux_w_sel_fsm;
    wire [9:0]  ext_w_dp     = modo_carga ? ext_w_ld      : ext_w_fsm;

    // -------------------------------------------------------
    // Datapath
    // -------------------------------------------------------
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

    // -------------------------------------------------------
    // FSM
    // -------------------------------------------------------
    wire pronto, overflow_fsm;

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

    // -------------------------------------------------------
    // Resultado em VA (FSM deixa sel_ra=2 no estado DONE)
    // -------------------------------------------------------
    wire [9:0]  resultado   = va;
    wire [19:0] resultado20 = {10'd0, resultado};

    // -------------------------------------------------------
    // Binário → BCD → 7 segmentos
    // -------------------------------------------------------
    wire [3:0] d0, d1, d2, d3, d4, d5, d6;

    bin2bcd_20 u_bcd (
        .bin  (resultado20),
        .bcd0 (d0), .bcd1 (d1),
        .bcd2 (d2), .bcd3 (d3),
        .bcd4 (d4), .bcd5 (d5), .bcd6 (d6)
    );

    bcd_7seg u_h0 (.bcd(d0), .seg(HEX0));
    bcd_7seg u_h1 (.bcd(d1), .seg(HEX1));
    bcd_7seg u_h2 (.bcd(d2), .seg(HEX2));
    bcd_7seg u_h3 (.bcd(d3), .seg(HEX3));

    // -------------------------------------------------------
    // LEDs
    // -------------------------------------------------------
    assign LEDR[9]   = pronto;
    assign LEDR[8]   = overflow_fsm;
    assign LEDR[7:0] = resultado[7:0];

    assign LEDG[7:0] = 8'b0;   // disponível para debug de estado

endmodule
