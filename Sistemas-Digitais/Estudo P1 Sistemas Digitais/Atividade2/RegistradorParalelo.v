module shift_reg_16(
    input clk,
    input rst_n,
    input [1:0] mode,
    input [15:0] d_in,
    output reg [15:0] q
);

always @(posedge clk or negedge rst_n) begin
    if(!rst_n)
        q <= 16'h0000;
    else 
    begin
        case (mode)
            2'b00 : q <= q;
            2'b01 : q <= d_in;
            2'b10 : q <= {1'b0, q[15:1]};
            2'b11 : q <= {q[14:0],1'b0}; 
            default: q <= q;
        endcase
    end
end

endmodule