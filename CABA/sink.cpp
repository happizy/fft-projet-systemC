/* fichier sink.cpp */
#include "sink.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void SINK::COMPORTEMENT() {
  int n = 0;
  std::ofstream realStream("out_real.txt");
  std::ofstream imagStream("out_imag.txt");

  std::ifstream realStream_ref("out_real_ref_valid.txt");
  std::ifstream imagStream_ref("out_imag_ref_valid.txt");

  float real, imag, real_ref, imag_ref, diff, max_error = 0.;
  data_req.write(SC_LOGIC_1);
  int i;
  if (!realStream || !imagStream || !realStream_ref || !imagStream_ref) {
    // cout<<"[SINK] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
  }
  wait(1);

  while (true) {
    if (data_valid.read() == SC_LOGIC_1) {
      real = (float)data_real.read();
      imag = (float)data_imag.read();
      realStream << real << endl;
      imagStream << imag << endl;
      n++;
      if (n >= SIZE) {
        n = 0;
      }
    }
    wait();
  }
}
