`timescale 1ns / 1ps


module Battleship_top(
    output [3:0] vgaRed,
    output [3:0] vgaBlue,
    output [3:0] vgaGreen,
    output Hsync,
    output Vsync,
    input btnC, btnU, btnD, btnR, btnL,
    input clk
    );
    
    //Declare intermediate signals used in the module.
    wire [6:0] cursorCor;
    wire [11:0] Grid_Color;
    wire [6:0] scanCor;
    wire [6:0] Place_ADDR;
    wire [6:0] Shoot_ADDR;
    wire Place_OE, Place_WE, Shoot_OE, Shoot_WE;
    wire [1:0] Place_DATA, Shoot_DATA;
    wire [1:0] placeinput, shootinput;
    wire [1:0] Place_info, Shoot_info;
    
    
    //Instantiate cursor module.
    cursor Curs1 (.left(left), .right(right), .down(down), 
            .up(up), .clk(clk), .coord(cursorCor), .rst_addr(1'b0));
            
    //Instantiate the button debounce module.
    debounce_buttons bdb (.clk(clk), .btnL(btnL), .btnC(btnC), .btnR(btnR), .btnU(btnU), .btnD(btnD), 
                          .left(left), .center(center), .right(right), .up(up), .down(down));
    
    
    //Instantiate system memory for shooting and placing.
    memory memPlace(.oe(Place_OE), .we(Place_WE), .clk(clk), .addr(Place_ADDR), .data(Place_DATA));
    memory memShoot(.oe(Shoot_OE), .we(Shoot_WE), .clk(clk), .addr(Shoot_ADDR), .data(Shoot_DATA));
    
    //Assign the data to connect to the intermediate input signal or high impedance depending on the write enable signals.
    assign Place_DATA = (Place_WE)? placeinput :2'bzz;
    assign Shoot_DATA = (Shoot_WE)? shootinput :2'bzz;
    
    //Instantiate gameplay module.
    gameplay G1(.clk(clk), .center(center), .Place_DATA(placeinput), .Shoot_DATA(shootinput), 
                .Place_WE(Place_WE), .Shoot_WE(Shoot_WE), .Place_OE(Place_OE), .Shoot_OE(Shoot_OE),
                .cursorCor(cursorCor), .scanCor(scanCor), .Place_ADDR(Place_ADDR), .Shoot_ADDR(Shoot_ADDR), .Shoot_info(Shoot_info));
    
    //Instantiate the VGA module to display.
    VGA_out V1(.clk(clk), .reset(1'b0), .vsync(Vsync), .hsync(Hsync),
                .red(vgaRed), .blue(vgaBlue), .green(vgaGreen), .cursorCor(cursorCor), .scanCor(scanCor), .Grid_Color(Grid_Color));
    
    //Instantiate the color assignment module for the VGA display.            
    color_assignment C1(
    .Place_DATA(Place_info),
    .Shoot_DATA(Shoot_info),
    .Place_OE(Place_OE),
    .Shoot_OE(Shoot_OE),
    .Grid_Color(Grid_Color)
    );

    //Assign the intermediate signals for the data to connect to the output data or high impedance depending on the output enable signals.
    assign Place_info = Place_OE ? Place_DATA : 2'bzz;
    assign Shoot_info = Shoot_OE ? Shoot_DATA : 2'bzz;              
    
endmodule
