`timescale 1ps/1ps
module lookahead_tb;
reg [3:0] a;
reg [3:0] b;
reg cin;
wire [3:0] soma;
wire cout;

lookahead utt(
    .a(a),
    .b(b),
    .cin(cin),
    .soma(soma),
    .cout(cout)
);

initial begin
    $monitor("tempo = %0t valor a = %b valor b = %b cin = %b, soma = %b , cout = %b", $time,a,b,cin,soma,cout);
    a = 4'b0001;
    b = 4'b0010;
    cin = 0;
    #10;

    a = 4'b0101;
    b = 4'b0011;
    cin = 0;
    #10;
    
    a = 4'b1111;
    b = 4'b0001;
    cin = 0;
    #10;
    
    a = 4'b1010;
    b = 4'b0101;
    cin = 1;
    #10;
    $finish;
end
endmodule
