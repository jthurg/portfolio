`timescale 1ns / 1ps

module gameplay(
input clk,
input center,
input [6:0] cursorCor,
input [6:0] scanCor,
input [1:0] Shoot_info,
output reg [6:0] Place_ADDR,
output reg [6:0] Shoot_ADDR,
output reg [1:0] Place_DATA,
output reg [1:0] Shoot_DATA,
output reg Place_WE,
output reg Shoot_WE,
output reg Place_OE,
output reg Shoot_OE
);
    
//Define parameters for state names and ship count..
parameter placeOE = 3'b000;
parameter placeWE = 3'b001;
parameter shootOE = 3'b010;
parameter readShoot = 3'b011;
parameter shootWE = 3'b100;
parameter [2:0] shipNum = 3'b101;

//Define intermediate signals.
reg [2:0] state, next_state;
reg [2:0] shipsPlaced;
reg [1:0] readinfo;

//Generate a pulse from the center button input to help acount for bouncing.
 create_pulse_from_step centerPulse (.clk(clk), .step(center), .pulse(inc_addr_pulseCenter));

//Define the next state logic.
initial shipsPlaced = 3'b000;
initial state = placeOE;
always @(*)
    begin
        
    case(state)
    
        //If placeOE state, data with ship location info should be output to the VGA to show
        //where ships have already been placed.
        placeOE:
            begin
                Place_DATA = 2'b00;
                Shoot_DATA = 2'b00;
                Place_ADDR = scanCor;
                Shoot_ADDR = 7'hxx;
                Place_WE = 0;
                Place_OE = 1;
                Shoot_WE = 0;
                Shoot_OE = 0;
                
                //If center button is pressed, then move to the placeWE state to put the ship
                //location in memory.
                 if (inc_addr_pulseCenter)
                    begin
                        next_state = placeWE;
                    end
                 else 
                     begin
                         next_state = state;
                         shipsPlaced = shipsPlaced;
                     end
             end
        
        //If in the placeWE state, the location for the ship being placed will be written to that corresponding
        //location in both placing and shooting memories.
        placeWE:
            begin
                Place_ADDR = cursorCor;
                Shoot_ADDR = cursorCor;
                Place_DATA = 2'b10;
                Shoot_DATA = 2'b10;
                Place_WE = 1;
                Place_OE = 0;
                Shoot_WE = 1;
                Shoot_OE = 0;
                
                 //If the user has placed all the ships, move to shooOE state, else return to the placeOE state.
                 if (shipsPlaced == shipNum - 1)
                    begin
                        next_state = shootOE;
                    end
                 else next_state = placeOE;
             end
        
        //If in the shootOE state, the user can move the cursor and hit the center on a location
        //they want to fire at. The data for each location on the grid is being output to the VGA 
        //to show if ships are hit or not.
        shootOE:
            begin
                Place_DATA = 2'b00;
                Shoot_DATA = 2'b00;
                Place_ADDR = 7'hxx;
                Shoot_ADDR = scanCor;
                Place_WE = 0;
                Place_OE = 0;
                Shoot_WE = 0;
                Shoot_OE = 1;
                
                //If the center button is pressed, move to the readShoot state.
                 if (inc_addr_pulseCenter)
                    begin
                        next_state = readShoot;
                    end
                 else next_state = state;
             end
             
        //If in readShoot state, read the data at the location of the cursor and latch the value.
        //Then move to shootWE state.     
        readShoot:
            begin
                
                Place_DATA = 2'b00;
                Shoot_DATA = 2'b00;
                Place_ADDR = 7'hxx;
                Shoot_ADDR = cursorCor;
                Place_WE = 0;
                Place_OE = 0;
                Shoot_WE = 0;
                Shoot_OE = 1;
                next_state = shootWE;
            end
            
        //If in the shootWE state, update the data at the cursor location to indicate that the location
        //has been fired at. Then return to the shootOE state.
        shootWE:
            begin
                Place_ADDR = 7'hxx;
                Shoot_ADDR = cursorCor;
                Place_DATA = 2'bxx;
                Shoot_DATA = {readinfo[1],1'b1};
                Place_WE = 0;
                Place_OE = 0;
                Shoot_WE = 1;
                Shoot_OE = 0;
                next_state = shootOE;
                
             end
        
        //The default state implies the data is irrelevant. Move to the shootOE state.     
        default: 
            begin
                Place_ADDR = 7'hxx;
                Shoot_ADDR = 7'hxx;
                Place_DATA = 2'bxx;
                Shoot_DATA = 2'bxx;
                Place_WE = 0;
                Place_OE = 0;
                Shoot_WE = 0;
                Shoot_OE = 0;
                next_state = shootOE;
            end
    endcase
    
    end
    
////Pass the next state to the state on the rising edge.
always @(posedge clk)
    begin

        //Increment the ships placed by 1 if Place_WE is asserted.
        if (Place_WE)
            begin
                shipsPlaced <= shipsPlaced + 1;
            end
        else 
            begin
                shipsPlaced <= shipsPlaced;
            end
            
        //Latch the info from the memory location during the readShoot state.
        if (state == readShoot)
            readinfo <= Shoot_info;
        else
            readinfo <= readinfo;
        
        //Pass the next state to the current state.    
        state <= next_state;
    end

    
endmodule
