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

module memory_sequence (
    input clk,  
    input write_enable,
    input [3:0]write_addres,
    input [1:0]write_data,
    input [3:0]read_addres,
    output [1:0]read_data
);
    reg [1:0] memoria [15:0];
    always @(posedge clk) begin
        if(write_enable == 1'b1) memoria[write_addres] <= write_data;
    end
    assign read_data = memorai[write_addres];
endmodule
