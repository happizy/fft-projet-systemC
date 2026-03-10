#ifndef SINK_H
#define SINK_H
#ifndef SIZE
#define SIZE 8
#define BUS_DEPTH (2 * SIZE)
#endif
#include "systemc.h"

SC_MODULE(SINK) {
  sc_in_clk clk;
  // sc_fifo_in<float> in;
  sc_in<float> data_imag, data_real;
  sc_in<sc_logic> data_valid;
  sc_out<sc_logic> data_req;

  void COMPORTEMENT();

  SC_CTOR(SINK) {
    SC_THREAD(COMPORTEMENT);
    sensitive << clk.pos();
  }
};
#endif
