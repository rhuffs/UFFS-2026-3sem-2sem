// Testbench — Datapath (sem MUX_A / MUX_B)
`timescale 1ns/1ps
//`include "datapath.v"

module tb_datapath;

    // ---- Entradas ----
    reg        clk;
    reg        escreve;
    reg [2:0]  sel_ra, sel_rb, sel_rw;
    reg [2:0]  sel_op;
    reg        mux_w_sel;
    reg [9:0]  ext_w;

    // ---- Saídas ----
    wire [9:0] va, vb, s;
    wire       z, c;

    // ---- Instância ----
    datapath dut (
        .clk       (clk),
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
        .z         (z),
        .c         (c)
    );

    // ---- Clock 100 MHz ----
    initial clk = 0;
    always #5 clk = ~clk;

    // ---- Contadores de pass/fail ----
    integer pass_count, fail_count;

    // ---- Tarefa: verificar resultado ----
    task check;
        input [63:0] descricao;     // etiqueta para display (não usado diretamente)
        input [9:0]  s_esperado;
        input        z_esperado;
        input        c_esperado;
        begin
            if (s === s_esperado && z === z_esperado && c === c_esperado) begin
                $display("  [PASS] S=%0d Z=%b C=%b", s, z, c);
                pass_count = pass_count + 1;
            end else begin
                $display("  [FAIL] S=%0d(esp=%0d) Z=%b(esp=%b) C=%b(esp=%b)",
                         s, s_esperado, z, z_esperado, c, c_esperado);
                fail_count = fail_count + 1;
            end
        end
    endtask

    // ---- Tarefa: carregar registrador via ext_w ----
    task load_reg;
        input [2:0]  rw;
        input [9:0]  val;
        begin
            sel_rw    = rw;
            ext_w     = val;
            mux_w_sel = 1;      // Usa ext_w
            escreve   = 0; #2;
            escreve   = 1; #2;  // Borda de subida → escrita
            escreve   = 0; #2;
        end
    endtask

    // ---- Tarefa: salvar resultado da ULA no banco ----
    task save_ula_result;
        input [2:0] rw;
        begin
            sel_rw    = rw;
            mux_w_sel = 0;      // Usa saída S da ULA
            escreve   = 0; #2;
            escreve   = 1; #2;
            escreve   = 0; #2;
        end
    endtask

    integer i;

    initial begin
        $dumpfile("tb_datapath.vcd");
        $dumpvars(0, tb_datapath);

        pass_count = 0;
        fail_count = 0;

        // Inicialização
        escreve = 0; mux_w_sel = 0;
        sel_ra = 0; sel_rb = 0; sel_rw = 0; sel_op = 0; ext_w = 0;
        #10;

        // ----------------------------------------------------------------
        // 1. CARGA DO BANCO DE REGISTRADORES
        // ----------------------------------------------------------------
        $display("\n=== 1. Carga do banco de registradores ===");
        load_reg(3'd0, 10'd15);    // R0 = 15
        load_reg(3'd1, 10'd4);     // R1 = 4
        load_reg(3'd2, 10'd100);   // R2 = 100
        load_reg(3'd3, 10'd1023);  // R3 = 1023 (máximo 10 bits)
        load_reg(3'd4, 10'd0);     // R4 = 0
        load_reg(3'd5, 10'd3);     // R5 = 3

        // ----------------------------------------------------------------
        // 2. VERIFICAÇÃO DA LEITURA DO BANCO
        // ----------------------------------------------------------------
        $display("\n=== 2. Leitura do banco ===");
        sel_ra = 3'd0; sel_rb = 3'd1; #3;
        $display("  Lendo R0 e R1: VA=%0d VB=%0d (esp: 15 e 4)", va, vb);
        if (va === 10'd15 && vb === 10'd4) begin
            $display("  [PASS]"); pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL]"); fail_count = fail_count + 1;
        end

        sel_ra = 3'd2; sel_rb = 3'd3; #3;
        $display("  Lendo R2 e R3: VA=%0d VB=%0d (esp: 100 e 1023)", va, vb);
        if (va === 10'd100 && vb === 10'd1023) begin
            $display("  [PASS]"); pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL]"); fail_count = fail_count + 1;
        end

        // ----------------------------------------------------------------
        // 3. TODAS AS OPERAÇÕES DA ULA (R0=15, R1=4)
        // ----------------------------------------------------------------
        $display("\n=== 3. Operações da ULA (R0=15, R1=4) ===");
        sel_ra = 3'd0; sel_rb = 3'd1; #3;

        $display("  000 A*B  : %0d * %0d", va, vb);
        sel_op = 3'b000; #3; check("mul", 10'd60,  1'b0, 1'b0);

        $display("  001 A<<B : %0d << %0d", va, vb);
        sel_op = 3'b001; #3; check("sll", 10'd240, 1'b0, 1'b0);

        $display("  010 A>>B : %0d >> %0d", va, vb);
        sel_op = 3'b010; #3; check("srl", 10'd0,   1'b1, 1'b1);  // 15>>4=0, C=último bit deslocado (bit[3]=1)

        $display("  011 A+B  : %0d + %0d", va, vb);
        sel_op = 3'b011; #3; check("add", 10'd19,  1'b0, 1'b0);

        $display("  100 A AND B: %0d AND %0d", va, vb);
        sel_op = 3'b100; #3; check("and", 10'd4,   1'b0, 1'b0);  // 01111 & 00100 = 00100 = 4

        $display("  101 A/B  : %0d / %0d", va, vb);
        sel_op = 3'b101; #3; check("div", 10'd3,   1'b0, 1'b0);  // 15/4 = 3

        $display("  110 A-B  : %0d - %0d", va, vb);
        sel_op = 3'b110; #3; check("sub", 10'd11,  1'b0, 1'b0);

        $display("  111 A XOR B: %0d XOR %0d", va, vb);
        sel_op = 3'b111; #3; check("xor", 10'd11,  1'b0, 1'b0);  // 01111 ^ 00100 = 01011 = 11

        // ----------------------------------------------------------------
        // 4. FLAG ZERO
        // ----------------------------------------------------------------
        $display("\n=== 4. Flag Zero (R4=0, R4=0) ===");
        sel_ra = 3'd4; sel_rb = 3'd4; sel_op = 3'b011; #3;
        $display("  0 + 0 = %0d", s);
        check("zero_add", 10'd0, 1'b1, 1'b0);

        sel_ra = 3'd0; sel_rb = 3'd0; sel_op = 3'b110; #3;  // 15-15 = 0
        $display("  15 - 15 = %0d", s);
        check("zero_sub", 10'd0, 1'b1, 1'b0);

        // ----------------------------------------------------------------
        // 5. OVERFLOW / UNDERFLOW
        // ----------------------------------------------------------------
        $display("\n=== 5. Overflow na adição (R3=1023, R0=15) ===");
        sel_ra = 3'd3; sel_rb = 3'd0; sel_op = 3'b011; #3;
        $display("  1023 + 15 = %0d (esperado 14)", s);
        check("overflow_add", 10'd14, 1'b0, 1'b1);

        $display("\n=== 6. Underflow na subtração (R1=4, R2=100) ===");
        sel_ra = 3'd1; sel_rb = 3'd2; sel_op = 3'b110; #3;
        $display("  4 - 100 = %0d (esperado 928)", s);
        check("underflow_sub", 10'd928, 1'b0, 1'b1);

        // ----------------------------------------------------------------
        // 6. DIVISÃO POR ZERO
        // ----------------------------------------------------------------
        $display("\n=== 7. Divisão por zero (R0=15, R4=0) ===");
        sel_ra = 3'd0; sel_rb = 3'd4; sel_op = 3'b101; #3;
        $display("  15 / 0 → C=%b (esperado C=1)", c);
        if (c === 1'b1) begin
            $display("  [PASS]"); pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL]"); fail_count = fail_count + 1;
        end

        // ----------------------------------------------------------------
        // 7. ESCRITA DO RESULTADO DA ULA DE VOLTA NO BANCO
        // ----------------------------------------------------------------
        $display("\n=== 8. Pipeline: R6 = R0 + R1 (15+4=19) ===");
        sel_ra = 3'd0; sel_rb = 3'd1; sel_op = 3'b011; #3;
        save_ula_result(3'd6);
        sel_ra = 3'd6; #3;
        $display("  R6 = %0d (esperado 19)", va);
        if (va === 10'd19) begin
            $display("  [PASS]"); pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL]"); fail_count = fail_count + 1;
        end

        $display("\n=== 9. Pipeline: R7 = R6 * R5 (19*3=57) ===");
        sel_ra = 3'd6; sel_rb = 3'd5; sel_op = 3'b000; #3;
        save_ula_result(3'd7);
        sel_ra = 3'd7; #3;
        $display("  R7 = %0d (esperado 57)", va);
        if (va === 10'd57) begin
            $display("  [PASS]"); pass_count = pass_count + 1;
        end else begin
            $display("  [FAIL]"); fail_count = fail_count + 1;
        end

        // ----------------------------------------------------------------
        // 8. SHIFT COM CARRY
        // ----------------------------------------------------------------
        $display("\n=== 10. Shift left com overflow: R3=1023 << R1=4 ===");
        sel_ra = 3'd3; sel_rb = 3'd1; sel_op = 3'b001; #3;
        // 1023 = 0011_1111_1111 → << 4 → 1111_1111_0000 truncado a 10 bits = 11_1111_0000 = 1008
        // Mas bit saindo: sim → C=1
        $display("  1023 << 4 = %0d C=%b (esp S=1008, C=1)", s, c);
        check("sll_overflow", 10'd1008, 1'b0, 1'b1);

        // ----------------------------------------------------------------
        // Resultado final
        // ----------------------------------------------------------------
        $display("\n========================================");
        $display("  RESULTADO: %0d PASS, %0d FAIL", pass_count, fail_count);
        $display("========================================\n");

        $finish;
    end

endmodule
