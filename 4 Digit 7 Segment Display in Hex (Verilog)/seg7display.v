`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/23/2025 01:37:23 PM
// Design Name: 
// Module Name: seg7display
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

//Define the seg7display module and its signals.
module seg7display(
    input [3:0] sw,
    output reg [6:0] seg,
    output [3:0] an,
    output dp
    );
    
    //Select the rightmost digit and turn off the decimal.
    assign an = 4'b1110;
    assign dp = 1'b1;
    
    //Create cases for each number from 0-9 that we wish to represent.
    //It will turn on corresponding segments of the BCD with low assertion.
    always @(sw)
        case(sw)
            4'h0: seg = 7'b1000000;
            4'h1: seg = 7'b1111001;
            4'h2: seg = 7'b0100100;
            4'h3: seg = 7'b0110000;
            4'h4: seg = 7'b0011001;
            4'h5: seg = 7'b0010010;
            4'h6: seg = 7'b0000010;
            4'h7: seg = 7'b1111000;
            4'h8: seg = 7'b0000000;
            4'h9: seg = 7'b0011000;
            4'ha: seg = 7'b0001000;
            4'hb: seg = 7'b0000011;
            4'hc: seg = 7'b1000110;
            4'hd: seg = 7'b0100001;
            4'he: seg = 7'b0000110;
            4'hf: seg = 7'b0001110;
            default: seg = 7'b1111111;
        endcase
endmodule
