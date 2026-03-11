#ifndef FFT_H
#define FFT_H

#define N 8

#include <systemc.h>
#include "sink.h"
#include "source.h"

typedef struct{
    float real;
    float imag;
} complex_t;

/*
CLOCK: YES

SIGNALS: 4
  - data_valid_source    INPUT
  - data_req_source      OUTPUT

  - data_valid_sink      OUTPUT
  - data_req_sink        INPUT

FIFO: 4
  - real_fifo_source     INPUT
  - imag_fifo_source     INPUT

  - real_fifo_sink       OUTPUT
  - imag_fifo_sink       OUTPUT
*/

SC_MODULE(FFT)
    {
      public:
        sc_in_clk clk;

        sc_fifo_in<float> real_fifo_source;
        sc_fifo_in<float> imag_fifo_source;
        sc_in<sc_logic> data_valid_source;
        sc_out<sc_logic> data_req_source;
        
        sc_fifo_out<float> real_fifo_sink;
        sc_fifo_out<float> imag_fifo_sink;
        sc_out<sc_logic> data_valid_sink;
        sc_in<sc_logic> data_req_sink;

        SC_CTOR(FFT){
            SC_THREAD(comportement);
            sensitive << clk.pos();
        }
      private:
        void comportement();
        void butterfly(complex_t *p_twiddle, complex_t *p_in1, complex_t *p_in2, complex_t *p_out1, complex_t *p_out2);

    };
#endif

