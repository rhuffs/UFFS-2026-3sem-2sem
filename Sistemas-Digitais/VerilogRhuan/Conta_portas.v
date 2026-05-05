
module Conta_portas(
    input [9:0] SW,
    output reg [3:0] LEDG
);

always @(*) begin
    LEDG = SW[0] + SW[1] + SW[2] + SW[3] + SW[4] + SW[5] + SW[6] + SW[7] + SW[8] + SW[9];
end

endmodule

x