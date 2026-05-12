module registrador8 (
    input clk,
    input load,
    input [7:0] d,
    output reg [7:0] q
);

    always @(negedge clk) begin
        if (load)
            q <= d;
    end

endmodule


module cla8 (
    input [7:0] a,
    input [7:0] b,
    input cin,
    output [7:0] soma,
    output cout
);

    wire [7:0] p;
    wire [7:0] g;
    wire [8:0] c;

    assign c[0] = cin;

    assign p = a ^ b;
    assign g = a & b;

    assign c[1] = g[0] | (p[0] & c[0]);
    assign c[2] = g[1] | (p[1] & c[1]);
    assign c[3] = g[2] | (p[2] & c[2]);
    assign c[4] = g[3] | (p[3] & c[3]);
    assign c[5] = g[4] | (p[4] & c[4]);
    assign c[6] = g[5] | (p[5] & c[5]);
    assign c[7] = g[6] | (p[6] & c[6]);
    assign c[8] = g[7] | (p[7] & c[7]);

    assign soma = p ^ c[7:0];

    assign cout = c[8];

endmodule


module soma_sub (
    input [7:0] a,
    input [7:0] b,
    input op,
    output [7:0] resultado,
    output overflow,
    output zero
);

    wire [7:0] b_mod;
    wire cout;

    assign b_mod = op ? ~b : b;

    cla8 cla (
        .a(a),
        .b(b_mod),
        .cin(op),
        .soma(resultado),
        .cout(cout)
    );

    assign overflow = cout ^ resultado[7];

    assign zero = (resultado == 8'b00000000);

endmodule


module hex7seg (
    input [3:0] bin,
    output reg [6:0] seg
);

    always @(*) begin
        case(bin)

            4'h0: seg = 7'b1000000;
            4'h1: seg = 7'b1111001;
            4'h2: seg = 7'b0100100;
            4'h3: seg = 7'b0110000;
            4'h4: seg = 7'b0011001;
            4'h5: seg = 7'b0010010;
            4'h6: seg = 7'b0000010;
            4'h7: seg = 7'b1111000;
            4'h8: seg = 7'b0000000;
            4'h9: seg = 7'b0010000;
            4'hA: seg = 7'b0001000;
            4'hB: seg = 7'b0000011;
            4'hC: seg = 7'b1000110;
            4'hD: seg = 7'b0100001;
            4'hE: seg = 7'b0000110;
            4'hF: seg = 7'b0001110;

        endcase
    end

endmodule


module top (
    input [9:0] SW,
    input [0:0] KEY,

    output [7:0] LEDR,
    output [7:0] LEDG,

    output [6:0] HEX0,
    output [6:0] HEX1,
    output [6:0] HEX2,
    output [6:0] HEX3
);

    wire [7:0] A;
    wire [7:0] B;

    wire [7:0] resultado;

    wire overflow;
    wire zero;

    wire loadA;
    wire loadB;

    assign loadA = ~SW[8];
    assign loadB = SW[8];

    registrador8 regA (
        .clk(KEY[0]),
        .load(loadA),
        .d(SW[7:0]),
        .q(A)
    );

    registrador8 regB (
        .clk(KEY[0]),
        .load(loadB),
        .d(SW[7:0]),
        .q(B)
    );

    soma_sub ULA (
        .a(A),
        .b(B),
        .op(SW[9]),
        .resultado(resultado),
        .overflow(overflow),
        .zero(zero)
    );

    assign LEDR = resultado;

    assign LEDG[7] = overflow;
    assign LEDG[0] = zero;

    assign LEDG[6:1] = 6'b000000;

    hex7seg h0 (
        .bin(resultado[3:0]),
        .seg(HEX0)
    );

    hex7seg h1 (
        .bin(resultado[7:4]),
        .seg(HEX1)
    );

    assign HEX2 = 7'b1111111;
    assign HEX3 = 7'b1111111;

endmodule