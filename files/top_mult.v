// ============================================================
//  Top-Level — Multiplicação FSM + Datapath
//  Plataforma: Altera DE2 / Cyclone II (EP2C20F484C7)
//  Quartus 13.0 ou superior
//
//  ── Pinagem (DE2 padrão) ──────────────────────────────────
//    CLOCK_50   : clock do sistema (50 MHz)
//    KEY[0]     : clock manual da FSM  (push-button, ativo-baixo)
//    KEY[1]     : reset geral          (push-button, ativo-baixo)
//    SW[9]      : inicio  (0 = modo carga, 1 = inicia multiplicação)
//    SW[8]      : seleciona operando na carga (0 → R0=A, 1 → R1=B)
//    SW[7:0]    : valor a carregar no banco (8 bits, bits [9:8] = 00)
//
//  ── Saídas ────────────────────────────────────────────────
//    HEX0..HEX3 : resultado em decimal (4 dígitos, ativo-baixo)
//    HEX4..HEX5 : apagados
//    LEDR[9]    : pronto
//    LEDR[8]    : overflow (resultado > 1023)
//    LEDR[7:0]  : bits do resultado (debug)
// ============================================================

module top_mult (
    input  wire        CLOCK_50,
    input  wire [3:0]  KEY,       // KEY[0]=clk FSM, KEY[1]=reset (ativo-baixo)
    input  wire [17:0] SW,
    output wire [8:0]  LEDR,
    output wire [17:9] LEDG,      // LEDG[9]=pronto, LEDG[8]=overflow  (DE2)
    output wire [6:0]  HEX0,
    output wire [6:0]  HEX1,
    output wire [6:0]  HEX2,
    output wire [6:0]  HEX3,
    output wire [6:0]  HEX4,
    output wire [6:0]  HEX5
);

    // -------------------------------------------------------
    // Reset e clock da FSM
    // -------------------------------------------------------
    wire rst        = ~KEY[1];
    wire clk_pulso;               // pulso limpo vindo do debounce

    debounce u_deb (
        .clk_sys (CLOCK_50),
        .rst     (rst),
        .btn_n   (KEY[0]),
        .pulso   (clk_pulso)
    );

    // -------------------------------------------------------
    // Sinais de controle (FSM → datapath)
    // -------------------------------------------------------
    wire        escreve_fsm;
    wire [2:0]  sel_ra_fsm, sel_rb_fsm, sel_rw_fsm, sel_op_fsm;
    wire        mux_w_sel_fsm;
    wire [9:0]  ext_w_fsm;

    // -------------------------------------------------------
    // Sinais do datapath
    // -------------------------------------------------------
    wire [9:0]  va, vb, s_ula;
    wire        z_flag, c_flag;

    // -------------------------------------------------------
    // Modo carga vs. modo FSM
    //   SW[9]=0 → carga manual
    //   SW[9]=1 → executa multiplicação
    // -------------------------------------------------------
    wire modo_carga = ~SW[9];
    wire inicio     =  SW[9];

    // Controle no modo carga: escreve ext_w diretamente no banco
    wire [2:0]  sel_rw_ld    = SW[8] ? 3'd1 : 3'd0;  // 0→R0(A) / 1→R1(B)
    wire [9:0]  ext_w_ld     = {2'b00, SW[7:0]};
    wire        escreve_ld   = clk_pulso & modo_carga;

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
    // FSM de controle
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
    // Resultado: quando FSM está em DONE, sel_ra=2 → VA = R2
    // -------------------------------------------------------
    wire [9:0]  resultado   = va;
    wire [19:0] resultado20 = {10'd0, resultado};

    // -------------------------------------------------------
    // Conversão binário → BCD
    // -------------------------------------------------------
    wire [3:0] d0, d1, d2, d3, d4, d5, d6;

    bin2bcd_20 u_bcd (
        .bin  (resultado20),
        .bcd0 (d0),
        .bcd1 (d1),
        .bcd2 (d2),
        .bcd3 (d3),
        .bcd4 (d4),
        .bcd5 (d5),
        .bcd6 (d6)
    );

    // -------------------------------------------------------
    // Displays 7 segmentos (ativo-baixo)
    // -------------------------------------------------------
    bcd_7seg u_h0 (.bcd(d0), .seg(HEX0));
    bcd_7seg u_h1 (.bcd(d1), .seg(HEX1));
    bcd_7seg u_h2 (.bcd(d2), .seg(HEX2));
    bcd_7seg u_h3 (.bcd(d3), .seg(HEX3));
    assign HEX4 = 7'b1111111;
    assign HEX5 = 7'b1111111;

    // -------------------------------------------------------
    // LEDs — LEDG na DE2 (verde, ativo-alto)
    // -------------------------------------------------------
    assign LEDG[9] = pronto;
    assign LEDG[8] = overflow_fsm;

    // LEDR: bits do resultado para debug
    assign LEDR[8:0] = resultado[8:0];

endmodule
