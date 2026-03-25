#ifndef FFT_H
#define FFT_H
#ifndef SC_INCLUDE_FX
#define SC_INCLUDE_FX
#endif
#ifndef SIZE
#define SIZE 8
#define BUS_DEPTH (2 * SIZE)
#define FIXED_POINT_O 27
#define FIXED_POINT 23
#define Q_FORMAT_O 24
#define Q_FORMAT 18
#define Q_FORMAT_W 2
#endif
#include "sink.h"
#include "source.h"
#include <systemc.h>

template <int STAGE> struct complex_t {
  sc_fixed<FIXED_POINT + STAGE * 2, Q_FORMAT + STAGE * 2, SC_RND, SC_SAT> real;
  sc_fixed<FIXED_POINT + STAGE * 2, Q_FORMAT + STAGE * 2, SC_RND, SC_SAT> imag;
};

typedef struct {
  sc_fixed<FIXED_POINT, Q_FORMAT_W, SC_RND, SC_SAT> real;
  sc_fixed<FIXED_POINT, Q_FORMAT_W, SC_RND, SC_SAT> imag;
} twiddle_t;

SC_MODULE(FFT) {
public:
  sc_in_clk clk;
  sc_in<sc_fixed<FIXED_POINT, Q_FORMAT, SC_RND, SC_SAT>> data_imag_in,
      data_real_in;
  sc_out<sc_fixed<FIXED_POINT_O, Q_FORMAT_O, SC_RND, SC_SAT>> data_imag_out,
      data_real_out;
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
  template <int STAGE>
  void butterfly(twiddle_t * p_twiddle, complex_t<STAGE> * p_in1,
                 complex_t<STAGE> * p_in2, complex_t<STAGE + 1> * p_out1,
                 complex_t<STAGE + 1> * p_out2) {
    p_out1->real = p_in1->real + ((p_in2->real * p_twiddle->real) -
                                  (p_in2->imag * p_twiddle->imag));

    p_out1->imag = p_in1->imag + ((p_in2->real * p_twiddle->imag) +
                                  (p_in2->imag * p_twiddle->real));

    p_out2->real = p_in1->real - ((p_in2->real * p_twiddle->real) -
                                  (p_in2->imag * p_twiddle->imag));

    p_out2->imag = p_in1->imag - ((p_in2->real * p_twiddle->imag) +
                                  (p_in2->imag * p_twiddle->real));
  };
};
#endif
