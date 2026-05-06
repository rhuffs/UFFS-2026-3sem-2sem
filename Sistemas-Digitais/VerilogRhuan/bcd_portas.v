// Nome: Rhuan Leandro Paiva && Henrique Schmitz Nilson
// link do youtube: https://youtu.be/2pkWIt334uQ?si=YpB4Z-WWOUQv7UHY
`timescale 1ns/1ps
module bcd_portas(
    input [9:0] SW,
    output reg [6:0] HEX0,
    output reg [6:0] HEX1,
    output reg [6:0] HEX2,
    output reg [6:0] HEX3
);

reg [3:0] conta_SW;

always @(*) begin
    conta_SW = SW[0] + SW[1] + SW[2] + SW[3] + SW[4] +
               SW[5] + SW[6] + SW[7] + SW[8] + SW[9];

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
            HEX0 = 7'b1111111;
            HEX1 = 7'b1111111;
        end
    endcase
end

endmodule