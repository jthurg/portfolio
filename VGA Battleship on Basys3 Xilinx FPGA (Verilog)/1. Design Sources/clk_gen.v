`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2025 12:55:24 PM
// Design Name: 
// Module Name: clk_gen
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

//Define clk_gen module and signals.
module clk_gen #(parameter n = 1)(
    input clk,
    input rst,
    output clk_div
    );
    
    //Define a counter and set to 0 if reset is true, else increment counter each positive edge of clock.
    reg [25:0] counter;
     always @(posedge clk or posedge rst)
        begin
        if(rst)
            counter <= 0;
        else
            counter <= counter + 1;
        end
    
    //Assign the divided clock signal to be the n-th bit of the counter signal.
    assign clk_div = counter[n];
    
endmodule
