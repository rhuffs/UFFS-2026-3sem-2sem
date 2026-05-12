module jokempo(
	input  [9:0] SW,
	output [6:0] HEX0, HEX1, HEX2, HEX3
);
	wire [1:0] JOG1 = SW[1:0];
	wire [1:0] JOG2 = SW[6:5];

	always @(*) begin
		if(JOG1 == 2'b00 || JOG2 == 2'b00) begin
			HEX3 = 7'b0001100; // P
			HEX2 = 7'b1000111; // L
			HEX1 = 7'b0001000; // A
			HEX0 = 7'b0011001; // Y
		end
		else if(JOG1 == JOG2) begin
			HEX3 = 7'b0000110; // E (Empate)
			HEX2 = 7'b1111111; 
			HEX1 = 7'b1111111; 
			HEX0 = 7'b1111111;
		end
		else begin
			case(JOG1)
				2'b01: // PEDRA
					if (JOG2 == 2'b11) begin // Contra Tesoura: JOG1 vence
						HEX3 = 7'b1100001; // J
						HEX2 = 0100011;    // o (ou 1000000 para 0)
						HEX1 = 7'b0000010; // G
						HEX0 = 7'b1111001; // 1
					end
					else begin // Contra Papel: JOG2 vence
						HEX3 = 7'b1100001;
						HEX2 = 7'b1000000;
						HEX1 = 7'b0000010;
						HEX0 = 7'b0100100; // 2
					end

				2'b10: // PAPEL
					if (JOG2 == 2'b01) begin // Contra Pedra: JOG1 vence
						HEX3 = 7'b1100001;
						HEX2 = 7'b1000000;
						HEX1 = 7'b0000010;
						HEX0 = 7'b1111001;
					end
					else begin // Contra Tesoura: JOG2 vence
						HEX3 = 7'b1100001;
						HEX2 = 7'b1000000;
						HEX1 = 7'b0000010;
						HEX0 = 7'b0100100;
					end

				2'b11: // TESOURA
					if(JOG2 == 2'b10) begin // Contra Papel: JOG1 vence
						HEX3 = 7'b1100001;
						HEX2 = 7'b1000000;
						HEX1 = 7'b0000010;
						HEX0 = 7'b1111001;
					end
					else begin // Contra Pedra: JOG2 vence
						HEX3 = 7'b1100001;
						HEX2 = 7'b1000000;
						HEX1 = 7'b0000010;
						HEX0 = 7'b0100100;
					end

				default: begin
					HEX3 = 7'b1111111;
					HEX2 = 7'b1111111;
					HEX1 = 7'b1111111;
					HEX0 = 7'b1111111;
				end
			endcase
		end
	end
endmodule