/* fichier source.h */
#ifndef SOURCE_H
#define SOURCE_H
#ifndef SC_INCLUDE_FX
#define SC_INCLUDE_FX
#endif
#define FIXED_POINT 23
#define Q_FORMAT 18

#include <systemc.h>

SC_MODULE(SOURCE) {
  sc_in_clk clk;
  sc_out<sc_fixed<FIXED_POINT, Q_FORMAT, SC_RND, SC_SAT>> data_real, data_imag;
  sc_out<sc_logic> data_valid;
  sc_in<sc_logic> data_req;

  void COMPORTEMENT();

  SC_CTOR(SOURCE) {
    SC_THREAD(COMPORTEMENT);
    sensitive << clk.pos();
  }
};
#endif
