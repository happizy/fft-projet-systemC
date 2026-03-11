#ifndef SOURCE_H
#define SOURCE_H

#include "systemc.h"

/*
CLOCK: YES

SIGNALS: 2
  - data_req     INPUT
  - data_valid   OUTPUT

FIFO: 2
  - fifo_real    OUTPUT
  - fifo_imag    OUTPUT
*/

SC_MODULE(SOURCE)
{
  sc_in_clk    clk;
  
  sc_fifo_out<float> fifo_real;
  sc_fifo_out<float> fifo_imag;
  
  sc_out<sc_logic> data_valid;
  sc_in<sc_logic>  data_req;

  void COMPORTEMENT();

  SC_CTOR(SOURCE)
  {
    SC_THREAD(COMPORTEMENT);
    sensitive << clk.pos();
  }
};

#endif
