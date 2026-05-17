module jokenpo(
    input [1:0] j1,
    input [1:0] j2,
    output reg j1_win,
    output reg tie,
    output reg j2_win
);

    parameter nenhum = 2'b00;
    parameter pedra = 2'b01;
    parameter papel = 2'b10;
    parameter tesoura = 2'b11;


    always @(*) begin
        j1_win = 1'b0;
        tie = 1'b0;
        j2_win = 1'b0;

        case({j1,j2})
            {pedra, pedra} : tie = 1'b1;
            {papel, papel} : tie = 1'b1;
            {tesoura, tesoura} : tie = 1'b1;

            {pedra, tesoura} : j1_win = 1'b1;
            {papel, pedra} : j1_win = 1'b1;
            {tesoura, papel} : j1_win = 1'b1;

            {pedra, papel } : j2_win = 1'b1;
            {papel, tesoura } : j2_win = 1'b1;
            {tesoura, pedra } : j2_win = 1'b1;

            default : begin
                j1_win = 1'b0;
                j2_win = 1'b0;
                tie = 1'b1;
            end

        endcase

    end



endmodule