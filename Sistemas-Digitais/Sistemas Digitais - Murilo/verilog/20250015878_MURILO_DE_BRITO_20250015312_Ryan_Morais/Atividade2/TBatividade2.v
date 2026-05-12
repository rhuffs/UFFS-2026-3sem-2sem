`timescale 1ns/1ps

module tb_Atividade2;

    reg [9:0] SW;
    wire [6:0] HEX0, HEX1, HEX2, HEX3;

    // Instancia o módulo
    Atividade2 uut (
        .SW(SW),
        .HEX0(HEX0),
        .HEX1(HEX1),
        .HEX2(HEX2),
        .HEX3(HEX3)
    );

    initial begin
        $display("Iniciando testes...");

        // Caso 0: nenhuma chave ligada
        SW = 10'b0000000000;
        #10;

        // Caso 1: 1 chave ligada
        SW = 10'b0000000001;
        #10;

        // Caso 2: 2 chaves ligadas
        SW = 10'b0000000011;
        #10;

        // Caso 3: 5 chaves ligadas
        SW = 10'b0000011111;
        #10;

        // Caso 4: 10 chaves ligadas
        SW = 10'b1111111111;
        #10;

        // Caso 5: padrão alternado
        SW = 10'b1010101010;
        #10;

        // Caso 6: outro aleatório
        SW = 10'b1100110011;
        #10;

        $display("Fim dos testes.");
        $stop;
    end

endmodule
