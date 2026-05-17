module lookahead_4bits(
    input [3:0] a,
    input [3:0] b,
    input cin,
    output [3:0] soma,
    output cout
);

wire [3:0] p;
wire [3:0] g;

wire c1,c2,c3,c4;

assign p = a ^ b;
assign g = a & b;
assign c1 = g[0] | (p[0] & cin);
assign c2 = g[1] | (p[1]& g[0]) | (p[1] & p[0] & cin);
assign c3 = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & cin);
assign c4 = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]) | (p[3] & p[2] & p[1] & p[0] & cin);

assign soma[0] = p[0] ^ cin;
assign soma[1] = p[1] ^ c1;
assign soma[2] = p[2] ^ c2;
assign soma[3] = p[3] ^ c3;
assign cout = c4;

endmodule


module lookahead_16bits(
    input [15:0] a,
    input [15:0] b,
    input cin,
    output [15:0] soma,
    output cout
);

wire c1,c2,c3;

lookahead_4bits cla0(
    .a(a[3:0]),
    .b(b[3:0]),
    .cin(cin),
    .soma(soma[3:0]),
    .cout(c1)
);

lookahead_4bits cla1(
    .a(a[7:4]),
    .b(b[7:4]),
    .cin(c1),
    .soma(soma[7:4]),
    .cout(c2)
);

lookahead_4bits cla2(
    .a(a[11:8]),
    .b(b[11:8]),
    .cin(c2),
    .soma(soma[11:8]),
    .cout(c3)
);

lookahead_4bits cla3(
    .a(a[15:12]),
    .b(b[15:12]),
    .cin(c3),
    .soma(soma[15:12]),
    .cout(cout)
);

endmodule

module lookahead_32bits(
    input [31 : 0] a,
    input [31 : 0] b,
    input cin,
    output [31 : 0] soma,
    output cout
);

wire c1,c2;

lookahead_16bits cla0(
    .a(a[15:0]),
    .b(b[15:0]),
    .cin(cin),
    .soma(soma[15:0]),
    .cout(c1)
);

lookahead_16bits cla1(
    .a(a[31:16]),
    .b(b[31:16]),
    .cin(c1),
    .soma(soma[31:16]),
    .cout(cout)
);

endmodule