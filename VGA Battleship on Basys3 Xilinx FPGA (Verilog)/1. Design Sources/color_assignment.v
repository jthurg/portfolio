`timescale 1ns / 1ps

module color_assignment(
    input [1:0] Place_DATA,
    input [1:0] Shoot_DATA,
    input Place_OE,
    input Shoot_OE,
    output reg [11:0] Grid_Color
    );
    
    //Define parameters for color values.
    parameter LIGHTBLUE = 12'h8cf;
    parameter WHITE = 12'hfff;
    parameter BLACK = 12'h000;
    parameter RED = 12'hf00;
    parameter GREY = 12'h777;
    parameter GREEN = 12'h0c0;
    
    //Define parameters for the data at the memory location.
    parameter noShipNoHit = 2'b00;
    parameter noShipHit = 2'b01;
    parameter ShipNoHit = 2'b10;
    parameter ShipHit = 2'b11;
    
    //Determine Grid_color assignment based on data at the memory location.
    always @(*)
    begin
    
    //If Place_OE, the data is coming from the placing memory.
    if (Place_OE)
        case (Place_DATA)
            noShipNoHit : Grid_Color = LIGHTBLUE;
            noShipHit   : Grid_Color = LIGHTBLUE;
            ShipNoHit   : Grid_Color = GREY;
            ShipHit     : Grid_Color = GREY;
        endcase
        
     //If Shoot_OE, the data is coming from the shooting memory.
     else if (Shoot_OE)
            case (Shoot_DATA)
                noShipNoHit : Grid_Color = LIGHTBLUE;
                noShipHit   : Grid_Color = WHITE;
                ShipNoHit   : Grid_Color = LIGHTBLUE;
                ShipHit     : Grid_Color = RED;
            endcase
      else
        
        //The default Grid_Color should be light blue.
        Grid_Color = LIGHTBLUE;
     end
    
endmodule
