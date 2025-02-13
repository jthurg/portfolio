`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Create Date: 02/11/2025 02:47:49 PM 
// Module Name: hex_num_gen
// Project Name: 4 Digit 7 Segment Display in Hex
// Target Devices: Basys 3 Xilinx FPGA Board
//////////////////////////////////////////////////////////////////////////////////

//Define module for hex_num_gen and signals.
module hex_num_gen(
    input [3:0] digit_sel,
    input [15:0] sw,
    output reg [3:0] hex_num
    );
    
    //Define which switches coorelate to which anode being activated.
    always @*
        begin
            case(digit_sel)
                4'b1110: hex_num = sw[3:0];
                4'b1101: hex_num = sw[7:4];
                4'b1011: hex_num = sw[11:8];
                4'b0111: hex_num = sw[15:12];
                default: hex_num = 4'b0000;
            endcase
        end
        
endmodule
