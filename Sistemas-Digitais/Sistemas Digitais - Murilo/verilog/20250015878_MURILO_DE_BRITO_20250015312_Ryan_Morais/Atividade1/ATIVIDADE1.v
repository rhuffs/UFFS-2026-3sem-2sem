module ATIVIDADE1(
    input [9:0] SW,
    output reg[3:0] LEDG
);
    integer i;
    reg [3:0] resultado;
    always @(*) begin
        resultado = 4'b0;
        for(i = 0; i < 10; i=i+1) begin
            if(SW[i] == 1'b1) begin
				   resultado = resultado +  1'b1;
				end
        end
        LEDG = resultado;
    end
endmodule