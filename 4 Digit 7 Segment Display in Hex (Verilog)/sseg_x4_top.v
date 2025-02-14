`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Create Date: 02/11/2025 12:51:49 PM
// Module Name: sseg_x4_top
// Project Name: 4 Digit 7 Segment Display in Hex
// Target Devices: Basys 3 Xilinx FPGA Board
//////////////////////////////////////////////////////////////////////////////////

// define module and signals for sseg_x4_top
module sseg_x4_top(
    input clk,
    input btnC,
    input [15:0] sw,
    output dp,
    output [3:0] an,
    output [4:0] JA,
    output [6:0] seg
    );
    
    // instantiate the clk_gen module with 100MHz clock, btnC as a reset, and clkd as a divided clk signal
    clk_gen U1(.clk(clk), .rst(btnC), .clk_div(clkd));
    assign JA [4] = clkd;
    
    // define intermediary signals
    wire [3:0] not_used;  //this is input into seg7display for a signal that isn't used later
    wire [3:0] hex_num;   //input for hex_num_gen
    
    // instantiate digit selector with the clkd as clock input, btnC as reset and an as an output
    digit_selector U2(
        .clk(clkd),
        .rst(btnC),
        .digit_sel(an));
    
    // instantiate seg7display to display a hex number on one of the digits    
    seg7display U3(
        .seg(seg),
        .an(not_used),
        .dp(dp),
        .sw(hex_num));
    
    //instantiate hex number generate to generate a hex number depending on the digit select instantiation   
    hex_num_gen(
        .digit_sel(an),
        .sw(sw),
        .hex_num(hex_num));
        
    //giving JA[3:0] the an signal to probe with an oscilloscope
    assign JA[3:0] = an;
endmodule
