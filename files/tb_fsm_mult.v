// ============================================================
//  Testbench — FSM de Multiplicação + Datapath
// ============================================================
`timescale 1ns/1ps

// Inclui todos os módulos
`include "register_file.v"
`include "ula.v"
`include "datapath.v"
`include "fsm_mult.v"

module tb_fsm_mult;

    // ---- Entradas ----
    reg  clk, rst, inicio;

    // ---- Interface datapath ↔ FSM ----
    wire        escreve;
    wire [2:0]  sel_ra, sel_rb, sel_rw, sel_op;
    wire        mux_w_sel;
    wire [9:0]  ext_w;
    wire [9:0]  va, vb, s;
    wire        z_flag, c_flag;
    wire        pronto, overflow;

    // ---- Instância do Datapath ----
    datapath u_dp (
        .clk       (1'b0),      // banco usa escreve como clock (posedge escreve)
        .escreve   (escreve),
        .sel_ra    (sel_ra),
        .sel_rb    (sel_rb),
        .sel_rw    (sel_rw),
        .sel_op    (sel_op),
        .mux_w_sel (mux_w_sel),
        .ext_w     (ext_w),
        .va        (va),
        .vb        (vb),
        .s         (s),
        .z         (z_flag),
        .c         (c_flag)
    );

    // ---- Instância da FSM ----
    fsm_mult u_fsm (
        .clk       (clk),
        .rst       (rst),
        .inicio    (inicio),
        .escreve   (escreve),
        .sel_ra    (sel_ra),
        .sel_rb    (sel_rb),
        .sel_rw    (sel_rw),
        .sel_op    (sel_op),
        .mux_w_sel (mux_w_sel),
        .ext_w     (ext_w),
        .z_flag    (z_flag),
        .c_flag    (c_flag),
        .pronto    (pronto),
        .overflow  (overflow)
    );

    // ---- Clock ----
    initial clk = 0;
    always #10 clk = ~clk;   // 50 MHz

    // ---- Tarefa: carregar registrador diretamente ----
    // (simula carga prévia antes do inicio)
    task force_reg;
        input [2:0]  rw;
        input [9:0]  val;
        begin
            // Forçamos via u_dp.rf.regs (acesso direto na simulação)
            u_dp.rf.regs[rw] = val;
        end
    endtask

    // ---- Tarefa: rodar multiplicação e aguardar pronto ----
    task run_mult;
        input [9:0] a_val;
        input [9:0] b_val;
        input [19:0] esperado;
        reg   timeout;
        integer ciclos;
        begin
            // Carrega operandos
            force_reg(3'd0, a_val);
            force_reg(3'd1, b_val);
            // Constante R7 = 10 (usada pela FSM para parar o loop)
            force_reg(3'd7, 10'd10);

            // Reset + início
            rst = 1; inicio = 0;
            @(posedge clk); #1;
            rst = 0;
            @(posedge clk); #1;

            inicio = 1;

            // Aguarda pronto (máx 200 ciclos)
            ciclos  = 0;
            timeout = 0;
            while (!pronto && ciclos < 200) begin
                @(posedge clk); #1;
                ciclos = ciclos + 1;
            end
            if (ciclos >= 200) timeout = 1;

            inicio = 0;
            #5;

            // Lê resultado (FSM deixa sel_ra=2 → VA = R2)
            if (timeout)
                $display("[TIMEOUT] %0d x %0d após %0d ciclos", a_val, b_val, ciclos);
            else if (va == esperado[9:0] && (overflow == (esperado > 1023)))
                $display("[PASS] %0d x %0d = %0d  (pronto em %0d ciclos)", a_val, b_val, va, ciclos);
            else
                $display("[FAIL] %0d x %0d: got=%0d(ov=%b) esp=%0d(ov=%b)",
                         a_val, b_val, va, overflow, esperado[9:0], (esperado > 1023));
        end
    endtask

    initial begin
        $dumpfile("tb_fsm_mult.vcd");
        $dumpvars(0, tb_fsm_mult);

        rst = 1; inicio = 0;
        #50;

        $display("\n=== Testbench FSM Multiplicação ===\n");

        // Casos básicos
        run_mult(10'd0,  10'd5,    20'd0);      // 0 * 5 = 0
        run_mult(10'd1,  10'd1,    20'd1);      // 1 * 1 = 1
        run_mult(10'd3,  10'd7,    20'd21);     // 3 * 7 = 21
        run_mult(10'd15, 10'd4,    20'd60);     // 15 * 4 = 60
        run_mult(10'd100,10'd100,  20'd10000);  // 100 * 100 = 10000 (overflow!)
        run_mult(10'd31, 10'd31,   20'd961);    // 31 * 31 = 961
        run_mult(10'd32, 10'd32,   20'd1024);   // 32 * 32 = 1024 (overflow!)
        run_mult(10'd1023,10'd1,   20'd1023);   // max * 1 = 1023
        run_mult(10'd7,  10'd7,    20'd49);     // 7 * 7 = 49
        run_mult(10'd255,10'd4,    20'd1020);   // 255 * 4 = 1020

        $display("\n=== Fim dos testes ===\n");
        $finish;
    end

endmodule
