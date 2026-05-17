module ripple4(

    input [3:0] a,
    input [3:0] b,
    input cin,

    output [3:0] soma,
    output cout

);

assign {cout,soma} = a + b + cin;

endmodule




module carry_select_4bits(

    input [3:0] a,
    input [3:0] b,
    input cin,

    output [3:0] soma,
    output cout

);

wire [3:0] soma0;
wire [3:0] soma1;

wire cout0;
wire cout1;

ripple4 r0(

    .a(a),
    .b(b),
    .cin(0),
    .soma(soma0),
    .cout(cout0)

);

ripple4 r1(

    .a(a),
    .b(b),
    .cin(1),
    .soma(soma1),
    .cout(cout1)

);

assign soma = (cin == 0) ? soma0 : soma1;
assign cout = (cin == 0) ? cout0 : cout1;

endmodule