//  main.cpp
// Testbench pour FFT avec donn�es en flottant

#include "main.h"
#include <systemc.h>

int sc_main(int argc, char *argv[]) {

  // Instanciation du TOP
  TOP mainTop("top");

  // Creation des traces
  sc_trace_file *tf = sc_create_vcd_trace_file("trace");
  tf->set_time_unit(1, SC_NS);
  // ATTENTION:
  // on peut pas faire ceci:
  // sc_trace(tf, mainTop.source_fft, "fifo1");
  // MAIS il faut faire appel a la methode
  // trace() du canal que l'on veut suivre
  // mainTop.source_fft.trace(tf);
  // mainTop.fft_sink.trace(tf);

  sc_trace(tf, mainTop.data_imag_in, "source_imag");
  sc_trace(tf, mainTop.data_real_in, "source_real");
  sc_trace(tf, mainTop.data_imag_out, "sink_imag");
  sc_trace(tf, mainTop.data_real_out, "sink_real");
  sc_trace(tf, mainTop.data_valid_source, "source_valid");
  sc_trace(tf, mainTop.data_req_source, "source_req");
  sc_trace(tf, mainTop.data_valid_sink, "sink_valid");
  sc_trace(tf, mainTop.data_req_sink, "sink_req");
  sc_trace(tf, mainTop.clk, "clk");

  // Lancement de la simulation
  sc_start(2000, SC_NS);

  // Fin
  cout << "Finished at " << sc_time_stamp() << "\n";
  // Fermeture du fichier de traces
  sc_close_vcd_trace_file(tf);

  return 0;
}
