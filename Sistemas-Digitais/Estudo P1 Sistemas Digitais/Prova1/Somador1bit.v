module somador_subtrator4bits(
    input [3:0] a,
    input [3:0] b,
    input controle,
    input cin,
    output [3:0] soma,
    output cout
);

wire [3:0] b_neg;
wire c1, c2, c3;


assign b_neg = b ^ {4{controle}};


Somador1bit s0(
    .a(a[0]),
    .b(b_neg[0]),
    .cin(controle),
    .soma(soma[0]),
    .cout(c1)
);


Somador1bit s1(
    .a(a[1]),
    .b(b_neg[1]),
    .cin(c1),
    .soma(soma[1]),
    .cout(c2)
);


Somador1bit s2(
    .a(a[2]),
    .b(b_neg[2]),
    .cin(c2),
    .soma(soma[2]),
    .cout(c3)
);


Somador1bit s3(
    .a(a[3]),
    .b(b_neg[3]),
    .cin(c3),
    .soma(soma[3]),
    .cout(cout)
);

endmodule