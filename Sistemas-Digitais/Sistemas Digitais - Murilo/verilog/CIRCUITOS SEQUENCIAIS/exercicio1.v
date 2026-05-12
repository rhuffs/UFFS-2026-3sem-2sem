module shift_reg_16(
    input wire clk,
    input wire rst_n,
    input wire [1:0] mode,
    input wire [15:0] d_in,
    output reg [15:0] q
);

always @(posedge clk or negedge rst_n) begin
    //reset
    if(!rst_n) begin
        q <= 16'h000;
    end
    else begin
        case (mode)
            2'b00:begin
                //mantém o valor atual
                q <= q;
            end
            2'b01: begin
                //carrega o dado enviado
                q <= d_in;
            end
            2'b10: begin
               //Desloca o bit para direita
               q <= {1'b0, q[15:1]};
            end
            2'b11: begin
                //desloca o bit para equerda
                q <= {q[14:0], 1'b0};
            end
            //caso der merda
            default q <= q;
        endcase
    end
end
endmodule