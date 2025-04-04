`timescale 1ns / 1ps

// the following module transforms a single step into a pulse lasting exactly one clock cycle
module create_pulse_from_step (
     input clk,
     input step,
     output pulse //pulse lasting exactly one clock cycle for each input step
     );
     reg step_tm1, step_tm2;
     
     initial step_tm1 = 1'b0;
     initial step_tm2 = 1'b0;
     always @ (posedge clk) 
     begin
       step_tm1 <= step;
       step_tm2 <= step_tm1;
     end
      
     assign pulse = step_tm1 && !step_tm2;
endmodule