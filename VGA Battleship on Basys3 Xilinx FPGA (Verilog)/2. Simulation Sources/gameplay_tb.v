`timescale 1ns / 1ps

module tb_gameplay;
    // Testbench signals
    reg clk;
    reg center;
    reg [6:0] cursorCor;
    reg [6:0] scanCor;
    wire [6:0] Place_ADDR;
    wire [6:0] Shoot_ADDR;
    wire [1:0] Place_DATA;
    wire [1:0] Shoot_DATA;
    wire Place_WE;
    wire Shoot_WE;
    wire Place_OE;
    wire Shoot_OE;

    // Instantiate the gameplay module
    gameplay uut (
        .clk(clk),
        .center(center),
        .cursorCor(cursorCor),
        .scanCor(scanCor),
        .Place_ADDR(Place_ADDR),
        .Shoot_ADDR(Shoot_ADDR),
        .Place_DATA(Place_DATA),
        .Shoot_DATA(Shoot_DATA),
        .Place_WE(Place_WE),
        .Shoot_WE(Shoot_WE),
        .Place_OE(Place_OE),
        .Shoot_OE(Shoot_OE)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // Clock with period of 10ns
    end

    // Test sequence
    initial begin
        // Initial values
        center = 0;
        cursorCor = 7'b0000000;  // Initial position
        scanCor = 7'b0000000;    // Initial position

        // Monitor the output values for debugging purposes
        $monitor("Time: %0t | state: %b | Place_ADDR: %b | Shoot_ADDR: %b | Place_DATA: %b | Shoot_DATA: %b | Place_WE: %b | Shoot_WE: %b | Place_OE: %b | Shoot_OE: %b",
                 $time, uut.state, Place_ADDR, Shoot_ADDR, Place_DATA, Shoot_DATA, Place_WE, Shoot_WE, Place_OE, Shoot_OE);

        // Apply stimulus
        // First step: Place the first ship
        #10 center = 1;  // Activate the center button pulse
        #10 center = 0;  // Deactivate the center button pulse

        // Step 2: Set cursorCor and scanCor for the second placement
        #20 cursorCor = 7'b0000001;
        #20 scanCor = 7'b0000000;

        // Second ship placement
        #10 center = 1;
        #10 center = 0;

        // Step 3: Move to the shoot phase
        #20 scanCor = 7'b0000010;  // Update scanCor for shooting phase
        #10 center = 1;
        #10 center = 0;

        // Step 4: Place data in the shoot phase
        #20 cursorCor = 7'b0000011;
        #20 scanCor = 7'b0000011;

        // End of the simulation
        #50 $finish;
    end

    // Optional: Monitor all the values
    initial begin
        $dumpfile("gameplay_tb.vcd");  // Output file for waveform viewing
        $dumpvars(0, tb_gameplay);     // Dump all variables for waveform viewing
    end

endmodule

