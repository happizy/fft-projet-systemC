//  main.h

#include "fft.h"
#include "sink.h"
#include "source.h"
#include <systemc.h>

SC_MODULE(TOP) {

  // signals
  sc_clock clk;
  sc_signal<sc_logic> data_valid_source, data_req_source, data_valid_sink,
      data_req_sink;
  sc_signal<float> data_imag_in, data_real_in, data_imag_out, data_real_out;
  // sc_fifo<float> source_fft;
  sc_fifo<float> fft_sink;

  // instanciate
  SOURCE SOURCE1;
  FFT FFT1;
  SINK SINK1;

  SC_CTOR(TOP)
      : clk("clk", 10, SC_NS, 0.5), data_imag_in("imag_in"),
        data_imag_out("imag_out"), data_real_in("real_in"),
        data_real_out("real_out"), data_valid_source("valid_source"),
        data_req_source("req_source"), data_valid_sink("valid_sink"),
        data_req_sink("req_sink"),
        // source_fft("source_fft", 16),
        fft_sink("fft_sink", 16), FFT1("FFT_PROCESS"),
        SOURCE1("SOURCE_PROCESS"), SINK1("SINK_PROCESS") {

    FFT1.clk(clk);
    FFT1.data_valid_source(data_valid_source);
    FFT1.data_req_source(data_req_source);
    FFT1.data_valid_sink(data_valid_sink);
    FFT1.data_req_sink(data_req_sink);
    FFT1.data_imag_in(data_imag_in);
    FFT1.data_real_in(data_real_in);
    FFT1.data_imag_out(data_imag_out);
    FFT1.data_real_out(data_real_out);
    // FFT1.input(source_fft);
    // FFT1.output(fft_sink);

    SOURCE1.clk(clk);
    SOURCE1.data_valid(data_valid_source);
    SOURCE1.data_req(data_req_source);
    SOURCE1.data_imag(data_imag_in);
    SOURCE1.data_real(data_real_in);
    // SOURCE1.out(source_fft);

    SINK1.clk(clk);
    SINK1.data_valid(data_valid_sink);
    SINK1.data_req(data_req_sink);
    SINK1.data_imag(data_imag_out);
    SINK1.data_real(data_real_out);
    // SINK1.in(fft_sink);
  }
};
