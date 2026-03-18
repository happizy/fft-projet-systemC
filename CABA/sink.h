#ifndef SINK_H
#define SINK_H
#ifndef SC_INCLUDE_FX
#define SC_INCLUDE_FX
#endif
#ifndef SIZE
#define SIZE 8
#define BUS_DEPTH (2 * SIZE)
#endif
#define FIXED_POINT 23
#define Q_FORMAT 18
#include <systemc.h>

SC_MODULE(SINK) {
  sc_in_clk clk;
  sc_in<sc_fixed<FIXED_POINT, Q_FORMAT>> data_imag, data_real;
  sc_in<sc_logic> data_valid;
  sc_out<sc_logic> data_req;

  void COMPORTEMENT();

  SC_CTOR(SINK) {
    SC_THREAD(COMPORTEMENT);
    sensitive << clk.pos();
  }
};
#endif