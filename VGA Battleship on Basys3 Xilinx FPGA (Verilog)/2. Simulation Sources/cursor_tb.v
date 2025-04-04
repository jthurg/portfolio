`timescale 1ns / 1ps

module tb_cursor;

    // Parameters
    parameter GRIDSIZE = 5;
    
    // Inputs to the cursor module
    reg left;
    reg center;
    reg right;
    reg down;
    reg up;
    reg clk;

    // Output from the cursor module
    wire [(GRIDSIZE - 1):0] coord;

    // Instantiate the cursor module
    cursor #(GRIDSIZE) uut (
        .left(left),
        .center(center),
        .right(right),
        .down(down),
        .up(up),
        .clk(clk),
        .coord(coord)
    );

    // Clock generation
    always begin
        clk = 0;
        #5 clk = 1;
        #5 clk = 0;
    end

    // Test procedure
    initial begin
        // Initialize inputs
        left = 0;
        center = 0;
        right = 0;
        down = 0;
        up = 0;

        // Start with the cursor at position 0
        $display("Initial coord: %d", coord);

        // Test moving right
        #10;
        right = 1; #10; right = 0;


        // Test moving down
        #10;
        down = 1; #10; down = 0;
        #10;
        down = 1; #10; down = 0;
        #10;
        down = 1; #10; down = 0;
        #10;
        down = 1; #10; down = 0;
        #10;
        down = 1; #10; down = 0;


        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        // Test moving left
        #10;
        left = 1; #10; left = 0;
        #10;
        left = 1; #10; left = 0;
        #10;
        left = 1; #10; left = 0;


        // Test moving up
        #10;
        up = 1; #10; up = 0;


        // Test moving right at boundary
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;
        #10;
        right = 1; #10; right = 0;


        // Test moving down at boundary
        #10;
        down = 1; #10; down = 0;


        // Test moving up at boundary
        #10;
        up = 1; #10; up = 0;


        // Test moving left at boundary
        #10;
        left = 1; #10; left = 0;

        // End the simulation
        $finish;
    end

endmodule
