module operation(
  input [9:0] SW,
  input [0:0] KEY,
  output reg [6:0] LEDR,
  output reg [6:0] LEDG,
  output reg [6:0] HEX0, HEX1, HEX3
);
  reg [7:0] vlr_A, vlr_B;
  reg [7:0] B_NP;
  wire [1:0] palavra;
  wire [7:0] resultado;
  wire cout;
  
  always @(negedge KEY[0]) begin
    if(SW[8] == 1'b0) begin
      HEX3 = 7'b0001000;
      palavra = 2'b01;
    end
    else begin
      vlr_B = SW[7:0];
      palavra = 2'b00;
    end
    
  end
  
  wire [1:0] palavra_final = (SW[9]) ? 2'b11 : estado_visual; 
  
  always @(*) begin
    if(SW[9] == 0) B_NP = vlr_B;
    else B_NP = ~ vlr_B;
  end
  
  wire c_intermediario;
        
  Cla_4 somador_metade_antes (
    .a(vlr_A[3:0]),
    .b(B_NP[3:0]),
    .Cin(SW[8]),             
    .sum(resultado[3:0]),
    .Cout(c_intermediario),  
    .propagate(),            
    .generatte(),            
    .P(),
    .G()
  );
        
  Cla_4 somador_metade_depois (
    .a(vlr_A[7:4]),
    .b(B_NP[7:4]),
    .Cin(c_intermediario),   
    .sum(resultado[7:4]),
    .Cout(cout),             
    .propagate(),
    .generatte(),
    .P(),
    .G()
  );
  

  display visualizacao(
    .RESULTADO(resultado_soma),
    .palavra(palavra_final),
    .HEX0(HEX0),
    .HEX1(HEX1),
    .HEX2(HEX2),
    .HEX3(HEX3)
  );
endmodule


//carrylookahead
module Cla_4(
  input [3:0]a,
  input [3:0]b,
  input Cin,
  output [3:0]sum,
  output Cout,
  output propagate,
  output generatte,
  output [3:0]P,
  output [3:0] G
);
  wire [4:0]C;
  assign C[0] = Cin;

    assign G = a & b;
    assign P = a ^ b;

    assign C[1] = G[0] | (P[0] & C[0]);
    assign C[2] = G[1] | (P[1] & C[1]);
    assign C[3] = G[2] | (P[2] & C[2]);
    assign C[4] = G[3] | (P[3] & C[3]);
    
    
    assign propagate = P[0] & P[1] & P[2] & P[3];
    
    assign generatte = G[3] |(P[3] & G[2]) |(P[3] & P[2] & G[1]) |(P[3] & P[2] & P[1] & G[0]);

    
    assign sum = P ^ C[3:0];

    assign Cout = C[4];
endmodule

//led
module display(
  input [7:0] RESULTADO,
  input [1:0] palavra,
  output reg [6:0] HEX0, HEX1, HEX2, HEX3
);

  integer i;
  reg [3:0] result;

  always @(*) begin
    HEX2 = 7'b1111111;
    case (palavra)
      2'b00: HEX3 = 7'b0000000;
      2'b01: HEX3 = 7'b0001000;
      2'b10: HEX3 = 7'b0010010;
    endcase
  end

  always @(*) begin
    result = 0; 
    for(i = 0; i < 7; i = i + 1) begin
      if(RESULTADO[i] == 1'b1)
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

      4'd10: begin HEX1 = 7'b1111001; HEX0 = 7'b1000000; end 
      4'd11: begin HEX1 = 7'b1111001; HEX0 = 7'b1111001; end 
      4'd12: begin HEX1 = 7'b1111001; HEX0 = 7'b0100100; end 
      4'd13: begin HEX1 = 7'b1111001; HEX0 = 7'b0110000; end 
      4'd14: begin HEX1 = 7'b1111001; HEX0 = 7'b0011001; end 

      default: begin
        HEX0 = 7'b1111111;
        HEX1 = 7'b1111111;
      end
    endcase
  end
endmodule