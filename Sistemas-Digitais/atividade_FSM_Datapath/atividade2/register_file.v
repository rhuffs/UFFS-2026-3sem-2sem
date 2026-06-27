// Banco de Registradores: 8 registradores de 10 bits
module register_file (
    input  wire        clk,
    input  wire        escreve,       // Escrita na borda de subida
    input  wire [2:0]  sel_ra,        // Seleção do registrador A (leitura)
    input  wire [2:0]  sel_rb,        // Seleção do registrador B (leitura)
    input  wire [2:0]  sel_rw,        // Seleção do registrador a escrever
    input  wire [9:0]  vw,            // Valor a escrever
    output wire [9:0]  va,            // Saída do registrador A
    output wire [9:0]  vb             // Saída do registrador B
);

    reg [9:0] regs [0:7];   // 8 registradores de 10 bits

    integer i;
    initial begin
        for (i = 0; i < 8; i = i + 1)
            regs[i] = 10'd0;
    end

    // Escrita síncrona na borda de subida de 'escreve'
    always @(posedge escreve) begin
        regs[sel_rw] <= vw;
    end

    // Leitura combinacional
    assign va = regs[sel_ra];
    assign vb = regs[sel_rb];

endmodule
