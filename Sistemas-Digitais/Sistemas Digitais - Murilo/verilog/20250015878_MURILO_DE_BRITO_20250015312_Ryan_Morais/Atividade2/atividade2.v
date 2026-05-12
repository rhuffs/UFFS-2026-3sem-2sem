module Atividade2(
    input [9:0] SW,
    output reg [6:0] HEX0, HEX1, HEX2, HEX3
);

  integer i;
  reg [3:0] result;

  always @(*) begin
    result = 0; 
    for(i = 0; i < 10; i = i + 1) begin
      if(SW[i] == 1'b1)
        result = result + 1'b1;
    end
  end

  always @(*) begin

    HEX0 = 7'b1111111;
    HEX1 = 7'b1111111;
    HEX2 = 7'b1111111;
    HEX3 = 7'b1111111;

    case(result)

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
        HEX0 = 7'b1000000; // 0
        HEX1 = 7'b1111001; // 1
      end

      default: begin
        HEX0 = 7'b1111111;
      end

    endcase
  end
endmodule
