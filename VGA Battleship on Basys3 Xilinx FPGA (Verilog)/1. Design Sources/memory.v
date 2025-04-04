`timescale 1ns / 1ps

//Define the memory module and signals.
module memory(
    input wire oe, we, clk,
    input wire [6:0] addr,
    inout wire [1:0] data
    );
    
    //Define parameters for grid size and the memory bit size and location size.
    parameter GRID_SIZE = 10;
    reg [1:0] mem[(GRID_SIZE * GRID_SIZE) - 1:0];
    
    //Assign data to memory at the address if output enable  and not write enable, else assign data to high impedance.
    assign data = (oe && !we)? mem[addr]:2'bzz;

    //At the rising clock edge, if write enable is high then pass data to the memory address.
    always @(posedge clk)
        begin
            if(we)
            mem[addr] <= data;
        end
 
endmodule
