`timescale 1ns / 1ps


module cursor(
    input left,
    input right,
    input down,
    input up,
    input clk,
    input rst_addr,
    output reg [6:0] coord
    );
    
    parameter GRID_SIZE = 10;
    
     create_pulse_from_step incRight (.clk(clk), .step(right), .pulse(inc_addr_pulseRight));
     create_pulse_from_step decLeft (.clk(clk), .step(left), .pulse(dec_addr_pulseLeft));
     create_pulse_from_step incUp (.clk(clk), .step(up), .pulse(inc_addr_pulseUp));
     create_pulse_from_step decDown (.clk(clk), .step(down), .pulse(dec_addr_pulseDown));
    
    
    
    
    initial coord = 0;
    always @(posedge clk)
    begin
        begin
            if (rst_addr)
                begin
                    coord <= 0;
                end
            else if (dec_addr_pulseLeft && (coord != 0))
                begin
                        coord <= coord - 1;
                end
            else if (inc_addr_pulseRight && ((coord + 1) < (GRID_SIZE * GRID_SIZE)))
                begin
                        coord <= coord + 1;
                end
            else if (dec_addr_pulseDown && ((coord + GRID_SIZE) < (GRID_SIZE * GRID_SIZE)))
                begin 
                        coord <= coord + GRID_SIZE;
                end
            else if (inc_addr_pulseUp && (coord > (GRID_SIZE - 1)))
                begin
                        coord <= coord - GRID_SIZE;
                end
            else coord <= coord;
        end
    end
    
    
    
endmodule
