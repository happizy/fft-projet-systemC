//  main.h

#include <systemc.h>
#include "source.h"
#include "fft.h"
#include "sink.h"

/*
CLOCK: YES

SIGNALS: 2
  - source_fft FIFO
  - fft_sink   FIFO
*/

SC_MODULE (TOP) {
  
  // signals
  sc_clock clk;
  sc_fifo<float> source_fft_real;
  sc_fifo<float> source_fft_imag;
  sc_fifo<float> sink_fft_real;
  sc_fifo<float> sink_fft_imag;    
  
  sc_signal<sc_logic> data_valid_source;
  sc_signal<sc_logic> data_req_source;

  sc_signal<sc_logic> data_valid_sink;
  sc_signal<sc_logic> data_req_sink;

  // instanciate
  SOURCE SOURCE1;
  FFT FFT1;
  SINK SINK1;

 SC_CTOR(TOP)
   :  clk("clk", 10, SC_NS, 0.5),
    source_fft_real("source_fft_real", 16),
    source_fft_imag("source_fft_imag", 16),
    sink_fft_real("sink_fft_real", 16),
    sink_fft_imag("sink_fft_imag", 16),
    FFT1("FFT_PROCESS"),
    SOURCE1("SOURCE_PROCESS"),
    SINK1("SINK_PROCESS")
  {
  // LINKING FFT
	FFT1.clk(clk);
	FFT1.real_fifo_source(source_fft_real);  
	FFT1.imag_fifo_source(source_fft_imag);  
	FFT1.real_fifo_sink(sink_fft_real);
	FFT1.imag_fifo_sink(sink_fft_imag);
  FFT1.data_valid_source(data_valid_source);
  FFT1.data_req_source(data_req_source);
  FFT1.data_valid_sink(data_valid_sink);
  FFT1.data_req_sink(data_req_sink);

  // LINKING SOURCE
	SOURCE1.clk(clk);
	SOURCE1.fifo_real(source_fft_real);
	SOURCE1.fifo_imag(source_fft_imag);
  SOURCE1.data_valid(data_valid_source);
  SOURCE1.data_req(data_req_source);

  // LINKING SINK
	SINK1.clk(clk);
	SINK1.fifo_real(sink_fft_real);
	SINK1.fifo_imag(sink_fft_imag);
  SINK1.data_valid(data_valid_sink);
  SINK1.data_req(data_req_sink);
  }
};

