`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2025 01:41:26 PM
// Design Name: 
// Module Name: memory_tb
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


module memory_tb( ); 
reg we, oe, clk; 
wire [1:0] data; 
reg [6:0] addr; 
reg [1:0] data_temp; 
parameter period = 10; 
memory u0 (.we(we), .oe(oe), .clk(clk), .data(data), .addr(addr)); 
 
assign data = we?data_temp:2'bZZ;  
always #(period/2) clk = ~clk;  
initial 
begin    clk = 0;    oe = 0;    we = 0; addr = 4'h0; data_temp = 2'b00;
     #5 we = 1'b1;    
     @(posedge clk) 
     #1          addr = 7'h0; data_temp = 2'b00;   // wait 1 ns before writing
     #period     addr = 7'h09; data_temp = 2'b01;        // writing to memory
     #period     addr = 7'h02; data_temp = 2'b10;    
     #period     addr = 7'h17; data_temp = 2'b11;
     #period     addr = 7'h0; we= 1'b0; oe = 1'b1;      // reading from memory
     #period     addr = 7'h09;    
     #period     addr = 7'h02;
     #period     addr = 7'h17; 
     #200 $finish;
end
endmodule

