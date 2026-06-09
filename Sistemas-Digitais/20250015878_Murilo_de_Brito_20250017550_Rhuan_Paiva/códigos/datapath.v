module GRANDOM (
    input clk,
    input rst,
    input enable,
    output [1:0] simbolo_randomico
);
    reg [3:0] LFSR;
    wire msb;
    assign msb = LFSR[3] ^ LFSR[2];

    always @(posedge clk or posedge rst) begin
        if(rst == 1'b1) LFSR <= 4'b0001;
        if(enable == 1'b1) LFSR <= {LFSR, msb};
    end
    assign simbolo_randomico = LFSR[1:0];
endmodule