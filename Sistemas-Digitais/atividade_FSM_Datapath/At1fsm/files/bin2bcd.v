// =============================================================
//  Conversor Binário 10 bits → BCD (Double Dabble)
//  Entrada: 10 bits (0 a 1023)
//  Saída:   4 dígitos BCD  d3 d2 d1 d0
//           Ex: 1023 → d3=1, d2=0, d1=2, d0=3
// =============================================================

module bin2bcd (
    input  wire [9:0] bin,
    output wire [3:0] d3,  // milhar
    output wire [3:0] d2,  // centena
    output wire [3:0] d1,  // dezena
    output wire [3:0] d0   // unidade
);
    reg [25:0] shift;  // 16 bits BCD (4 dígitos) + 10 bits binário
    integer k;

    always @(*) begin
        shift = 26'd0;
        shift[9:0] = bin;

        for (k = 0; k < 10; k = k + 1) begin
            if (shift[13:10] >= 5) shift[13:10] = shift[13:10] + 3;
            if (shift[17:14] >= 5) shift[17:14] = shift[17:14] + 3;
            if (shift[21:18] >= 5) shift[21:18] = shift[21:18] + 3;
            if (shift[25:22] >= 5) shift[25:22] = shift[25:22] + 3;
            shift = shift << 1;
        end
    end

    assign d0 = shift[13:10];
    assign d1 = shift[17:14];
    assign d2 = shift[21:18];
    assign d3 = shift[25:22];
endmodule
