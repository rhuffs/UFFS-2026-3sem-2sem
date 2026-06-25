// ============================================================
//  Conversor Binário → BCD (algoritmo Double Dabble)
//  Entrada: 20 bits (resultado da multiplicação 10×10)
//  Saída : 7 dígitos BCD (0..9 999 999 — resultado máx ≈ 1 046 529)
// ============================================================

module bin2bcd_20 (
    input  wire [19:0] bin,
    output wire [3:0]  bcd6,  // centena de milhar
    output wire [3:0]  bcd5,  // dezena de milhar
    output wire [3:0]  bcd4,  // milhar
    output wire [3:0]  bcd3,  // centena
    output wire [3:0]  bcd2,  // dezena
    output wire [3:0]  bcd1,  // unidade
    output wire [3:0]  bcd0   // não usado para resultados pequenos
);
    // Implementação combinacional via unroll do Double Dabble
    // Shifts: 20 iterações de 1 bit cada
    // BCD intermediário: 7 dígitos × 4 bits = 28 bits

    reg [47:0] bcd_r;  // 48 bits = 20 bin + 28 bcd (simplificado)
    integer    k;

    always @(*) begin
        bcd_r = 48'd0;
        bcd_r[19:0] = bin;

        for (k = 0; k < 20; k = k + 1) begin
            // Verifica cada grupo BCD de 4 bits e soma 3 se >= 5
            if (bcd_r[23:20] >= 5) bcd_r[23:20] = bcd_r[23:20] + 3;
            if (bcd_r[27:24] >= 5) bcd_r[27:24] = bcd_r[27:24] + 3;
            if (bcd_r[31:28] >= 5) bcd_r[31:28] = bcd_r[31:28] + 3;
            if (bcd_r[35:32] >= 5) bcd_r[35:32] = bcd_r[35:32] + 3;
            if (bcd_r[39:36] >= 5) bcd_r[39:36] = bcd_r[39:36] + 3;
            if (bcd_r[43:40] >= 5) bcd_r[43:40] = bcd_r[43:40] + 3;
            if (bcd_r[47:44] >= 5) bcd_r[47:44] = bcd_r[47:44] + 3;
            // Shift esquerda de 1 bit em todo o vetor
            bcd_r = bcd_r << 1;
        end
    end

    assign bcd0 = bcd_r[23:20];
    assign bcd1 = bcd_r[27:24];
    assign bcd2 = bcd_r[31:28];
    assign bcd3 = bcd_r[35:32];
    assign bcd4 = bcd_r[39:36];
    assign bcd5 = bcd_r[43:40];
    assign bcd6 = bcd_r[47:44];

endmodule
