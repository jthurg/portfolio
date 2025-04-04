`timescale 1ns / 1ps



module VGA_out(
    input clk,              // 100 MHz clock from Basys 3
    input reset,            // Reset signal
    input [11:0] Grid_Color,
    input [6:0] cursorCor,
    output reg hsync,       // Horizontal sync output
    output reg vsync,       // Vertical sync output
    output reg [3:0] red,   // 4-bit red color output
    output reg [3:0] green, // 4-bit green color output
    output reg [3:0] blue,   // 4-bit blue color output
    output [6:0] scanCor   //7-bit scanCoor output
);
    
    // VGA 640x480 @ 60Hz Timing Constants
    parameter H_PIXELS = 640;
    parameter H_FP = 16;      // Front porch
    parameter H_PW = 96;      // Sync pulse width
    parameter H_BP = 48;      // Back porch
    parameter H_TOTAL = 800;  // Total horizontal pixels

    parameter V_LINES = 480;
    parameter V_FP = 10;      // Front porch
    parameter V_PW = 2;       // Sync pulse width
    parameter V_BP = 33;      // Back porch
    parameter V_TOTAL = 525;  // Total vertical lines

    // Square Position & Size
    parameter SQUARE_SIZE = 400;     // Width & height of square
    parameter SQUARE_X_START = H_PIXELS / 2 - SQUARE_SIZE / 2; // X position of square (centered)
    parameter SQUARE_Y_START = V_LINES / 2 - SQUARE_SIZE / 2; // Y position of square (centered)
    
    //Grid size parameter
    parameter GRID_SIZE = 10;

    reg [9:0] h_count = 0; // Horizontal pixel counter (0-799)
    reg [9:0] v_count = 0; // Vertical line counter (0-524)
    wire clk_25MHz;     // 25 MHz clock
    
    //Declare an intermediate register to hold the color information for each channel to be displayed.
    reg [11:0] color;
    
    //Declare parameters for known colors.
    parameter WHITE = 12'hfff;
    parameter BLACK = 12'h000;
    parameter GREEN = 12'h0c0;
    
    //Assign the coordinate according to the current horizontal and vertical positions on the grid as the VGA scans.
    assign scanCor = ((h_count - SQUARE_X_START) / (SQUARE_SIZE / GRID_SIZE)) + (((v_count - SQUARE_Y_START) / (SQUARE_SIZE / GRID_SIZE)) * GRID_SIZE);

    //Assign red, green, and blue to their correlating bits on the color register.
    always@(*)
    begin
        red = color[11:8];
        green = color[7:4];
        blue = color[3:0];
    end

    // Clock Divider: Generate 25 MHz clock from 100 MHz input
    clk_gen C1(.clk(clk), .rst(reset), .clk_div(clk_25MHz));

    //Initialized the scanning start points.
    initial h_count = 0;
    initial v_count = 0;
    
    // VGA Timing Generator
    always @(posedge clk_25MHz or posedge reset) begin
        if (reset) begin
            h_count <= 0;
            v_count <= 0;
        end else begin
            // Increment horizontal counter
            if (h_count < H_TOTAL - 1)
                h_count <= h_count + 1;
            else begin
                h_count <= 0;
                // Increment vertical counter when horizontal completes
                if (v_count < V_TOTAL - 1)
                    v_count <= v_count + 1;
                else
                    v_count <= 0;
            end
        end
    end

    // Generate Sync Pulses
    always @(*) 
    begin
        hsync = (h_count >= (H_PIXELS + H_FP) && h_count < (H_PIXELS + H_FP + H_PW)) ? 0 : 1;
        vsync = (v_count >= (V_LINES + V_FP) && v_count < (V_LINES + V_FP + V_PW)) ? 0 : 1;
    end

    // Draw Square in Center
    always @(*) begin
        //Check if pixel is inside the monitor
        if (h_count < H_PIXELS && v_count < V_LINES) begin
        
            // Check if pixel is inside the grid
            if ((h_count >= SQUARE_X_START && h_count < SQUARE_X_START + SQUARE_SIZE + 1) &&
                (v_count >= SQUARE_Y_START && v_count < SQUARE_Y_START + SQUARE_SIZE + 1))                                           
                begin
                
                // check for border
                    if (((h_count - SQUARE_X_START) % (SQUARE_SIZE / GRID_SIZE) == 0) ||
                        ((v_count - SQUARE_Y_START) % (SQUARE_SIZE / GRID_SIZE) == 0))
                        begin
                          color = BLACK;
                        end
                        
                        // check if pixels are in the same box as the cursor
                    else if (scanCor == cursorCor)
                             begin 
                             
                             //color in the smaller cursor box
                                if ((((h_count - SQUARE_X_START) % (SQUARE_SIZE / GRID_SIZE) > (SQUARE_SIZE / GRID_SIZE) / 4)) && 
                                    (((h_count - SQUARE_X_START) % (SQUARE_SIZE / GRID_SIZE) < (SQUARE_SIZE / GRID_SIZE) * 3 / 4)) &&
                                    ((((v_count - SQUARE_Y_START) % (SQUARE_SIZE / GRID_SIZE) > (SQUARE_SIZE / GRID_SIZE) / 4)) &&
                                    ((v_count - SQUARE_Y_START) % (SQUARE_SIZE / GRID_SIZE) < (SQUARE_SIZE / GRID_SIZE) * 3 / 4)))
                                    color = GREEN;
                                else
                                    color = Grid_Color;
                             end
                    else 
                    begin
                        //Assign each square of the grid to be the Grid_color from color assignment depending
                        //on the data at each memory location of each square on the grid. That data is passed to 
                        //color_assignment module.
                        color = Grid_Color;
                    end
                end 
            else 
                begin
                
                    //If not in the grid but on the screen, then color the pixels white.
                    color = WHITE;
                end
        end else begin
            //If not in the grid and off the screen, then color the pixels black.
            color = BLACK;
        end
    end

endmodule
