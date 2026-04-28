module reg_file (
    input clk, //clock
    input rst_n, // reset em 0
    input we, // Write enable
    input [2:0] w_addr, //Write,
    input [15:0] w_data,
    input [2:0] r_addr_a,
    input [2:0] r_addr_b,
    output [15:0] r_data_a,
    output [15:0] r_data_b
);

reg [15:0] regs [0:7];
integer i;

// escrita + reset síncrono
always @(posedge clk) begin
    if (!rst_n) begin
        for (i = 0; i < 8; i = i + 1)
            regs[i] <= 16'b0;
    end else if (we) begin
        regs[w_addr] <= w_data;
    end
end

// leitura combinacional
assign r_data_a = regs[r_addr_a];
assign r_data_b = regs[r_addr_b];

endmodule