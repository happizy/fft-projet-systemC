#ifndef FFT_H
#define FFT_H
#ifndef SIZE
#define SIZE 8
#define BUS_DEPTH (2 * SIZE)
#endif
#include "sink.h"
#include "source.h"
#include <systemc.h>

typedef struct {
  float real;
  float imag;
} complex_t;

SC_MODULE(FFT) {
public:
  sc_in_clk clk;
  sc_in<float> data_imag_in, data_real_in;
  sc_out<float> data_imag_out, data_real_out;
  // sc_fifo_in<float> input;
  // sc_fifo_out<float> output;
  sc_in<sc_logic> data_valid_source;
  sc_in<sc_logic> data_req_sink;
  sc_out<sc_logic> data_valid_sink;
  sc_out<sc_logic> data_req_source;

  SC_CTOR(FFT) {
    SC_THREAD(comportement);
    sensitive << clk.pos();
  }

private:
  void comportement();
  void butterfly(complex_t * p_twiddle, complex_t * p_in1, complex_t * p_in2,
                 complex_t * p_out1, complex_t * p_out2);
};
#endif
