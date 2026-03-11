#ifndef SINK_H
#define SINK_H

#include "systemc.h"
#include "params.h"

#define N (FIFO_SIZE>>1)

/*
CLOCK: YES

SIGNALS: 2
  - data_req     OUTPUT
  - data_valid   INPUT

FIFO: 2
  - fifo_real    INPUT
  - fifo_imag    INPUT
*/

SC_MODULE(SINK) 
{
  sc_in_clk    clk;

  sc_fifo_in<float> fifo_real;
  sc_fifo_in<float> fifo_imag;

  sc_in<sc_logic>  data_valid;
  sc_out<sc_logic> data_req;

  void COMPORTEMENT(); 

  SC_CTOR(SINK)
  {
    SC_THREAD(COMPORTEMENT);
    sensitive << clk.pos();
  }    
};

#endif
