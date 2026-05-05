 

// 2) Faça o que se pede:

//     a) Implemente um circuito em Verilog que realiza a contagem da quantidade de chaves (SW[9:0]) que estão em nível lógico ALTO (1) e mostra essa quantidade nos displays de 7 segmentos (HEX3[6:0], HEX2[6:0], HEX1[6:0], HEX0[6:0]). Por exemplo, duas chaves SW em 1, valor mostrado: 0002

//    b) Implemente o Testbench do circuito verificando o funcionamento correto do circuito;

//   c) Implemente a solução do item 'a' na placa DE1 e faça um video mostrando o funcionamento do circuito.

module bcd_portas(
    input [9:0]SW,
    output reg [0:6] HEX0,
    output reg [0:6] HEX1,
    output reg [0:6] HEX2,
    output reg [0:6] HEX3
    
);


integer conta_SW;

always@(*) begin
    conta_SW = SW[0] + SW[1] + SW[2] + SW[3] + SW[4] + SW[5] + SW[6] + SW[7] + SW[8] + SW[9];

    HEX0 = 7'b1000000;
    HEX1 = 7'b1000000;
    HEX2 = 7'b1000000;
    HEX3 = 7'b1000000;

    case (conta_SW)
        4'd0: HEX0 = 7'b1000000;
        4'd1: HEX0 = 7'b1111001;
        4'd2: HEX0 = 7'b0100100;
        4'd3: HEX0 = 7'b0110000;
        4'd4: HEX0 = 7'b0011001;
        4'd5: HEX0 = 7'b0010010;
        4'd6: HEX0 = 7'b0000010;
        4'd7: HEX0 = 7'b1111000;
        4'd8: HEX0 = 7'b0000000;
        4'd9: HEX0 = 7'b0010000;
        4'd10: begin
            HEX0 = 7'b1000000;
            HEX1 = 7'b1111001;
        end

    endcase


end






endmodule