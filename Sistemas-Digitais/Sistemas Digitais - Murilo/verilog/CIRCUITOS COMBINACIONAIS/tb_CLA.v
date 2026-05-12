`timescale 1ns/1ps

module tb_cla_16;

    // Entradas (reg porque vamos mudar valores)
    reg [15:0] a, b;
    reg cin;

    // Saídas (wire porque vêm do módulo)
    wire [15:0] sum;
    wire cout;
    wire over_under;

    // Modelo de referência (17 bits pra pegar carry)
    reg [16:0] ref;

    // Instância do CLA
    cla_16 uut (
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout),
        .over_under(over_under)
    );

    // 🔍 Monitoramento contínuo
    initial begin
        $monitor("t=%0t | a=%h b=%h cin=%b | sum=%h cout=%b",
                  $time, a, b, cin, sum, cout);
    end

    // 🧠 Task para testar automaticamente
    task testa;
        begin
            #1;
            ref = a + b + cin;

            if ({cout, sum} !== ref) begin
                $display("❌ ERRO: a=%h b=%h cin=%b | esperado=%h obtido=%h",
                          a, b, cin, ref, {cout, sum});
            end else begin
                $display("✅ OK: a=%h b=%h cin=%b | resultado=%h",
                          a, b, cin, {cout, sum});
            end
        end
    endtask

    // 🚀 Testes
    initial begin

        $display("\n==== INÍCIO DOS TESTES ====\n");

        // 1. Soma sem carry
        a = 16'h0001; b = 16'h0001; cin = 0; testa();

        // 2. Carry simples
        a = 16'h0001; b = 16'h0001; cin = 1; testa();

        // 3. Overflow (carry out)
        a = 16'hFFFF; b = 16'h0001; cin = 0; testa();

        // 4. Máxima propagação de carry
        a = 16'hFFFF; b = 16'h0000; cin = 1; testa();

        // 5. Alternância de bits
        a = 16'hAAAA; b = 16'h5555; cin = 0; testa();

        // 6. Zeros absolutos
        a = 16'h0000; b = 16'h0000; cin = 0; testa();

        // 7. Valores aleatórios
        repeat (10) begin
            a = $random;
            b = $random;
            cin = $random % 2;
            testa();
        end

        // 8. Carry em posição intermediária
        a = 16'h00FF; b = 16'h0001; cin = 0; testa();

        // 9. Propagação parcial
        a = 16'h0FFF; b = 16'h0001; cin = 0; testa();

        $display("\n==== FIM DOS TESTES ====\n");

        $finish;
    end

endmodule