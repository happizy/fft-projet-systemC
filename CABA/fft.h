#ifndef FFT_H
#define FFT_H
#ifndef SC_INCLUDE_FX
#define SC_INCLUDE_FX
#endif
#ifndef SIZE
#define SIZE 8
#define BUS_DEPTH (2 * SIZE)
#define FIXED_POINT 23
#define Q_FORMAT 18
#define Q_FORMAT_W 2
#endif
#include "sink.h"
#include "source.h"
#include <systemc.h>

typedef struct {
  sc_fixed<FIXED_POINT, Q_FORMAT> real;
  sc_fixed<FIXED_POINT, Q_FORMAT> imag;
} complex_t;

typedef struct {
  sc_fixed<FIXED_POINT, Q_FORMAT_W> real;
  sc_fixed<FIXED_POINT, Q_FORMAT_W> imag;
} twiddle_t;

SC_MODULE(FFT) {
public:
  sc_in_clk clk;
  sc_in<sc_fixed<FIXED_POINT, Q_FORMAT>> data_imag_in, data_real_in;
  sc_out<sc_fixed<FIXED_POINT, Q_FORMAT>> data_imag_out, data_real_out;
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
  void butterfly(twiddle_t * p_twiddle, complex_t * p_in1, complex_t * p_in2,
                 complex_t * p_out1, complex_t * p_out2);
};
#endif
