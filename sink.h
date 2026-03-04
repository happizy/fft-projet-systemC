#ifndef SINK_H
#define SINK_H

#include "systemc.h"

 SC_MODULE(SINK) 
    {
         sc_in_clk    clk; 
         sc_fifo_in<float> in; 
         sc_in<sc_logic> data_valid;
         sc_out<sc_logic> data_req;

        void COMPORTEMENT(); 

         SC_CTOR(SINK)
              {
                     SC_THREAD(COMPORTEMENT);
                     sensitive << clk.pos();
              }    };
#endif
