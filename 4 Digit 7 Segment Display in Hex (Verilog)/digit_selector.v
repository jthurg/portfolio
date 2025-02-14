`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
// Create Date: 02/11/2025 02:08:17 PM
// Module Name: digit_selector
// Project Name: 4 Digit 7 Segment Display in Hex
// Target Devices: Basys 3 Xilinx FPGA Board
//////////////////////////////////////////////////////////////////////////////////

//Define module for digit_selector and signals.
module digit_selector(
    input clk,
    input rst,
    output reg [3:0] digit_sel = 4'b1111
    );
    
    //Turn of all anodes when rst is true, else assign the digit selector to be the first three bits shifted left 1 and the MSB becomes the LSB.
    always @(posedge clk, posedge rst)
        begin
            if (rst)
                digit_sel <= 4'b1111;
            else
                digit_sel <= {digit_sel[2:0], digit_sel[3]};
                
        end
        
endmodule
