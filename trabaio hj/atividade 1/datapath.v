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
