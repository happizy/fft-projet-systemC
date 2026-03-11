/* fichier source.cpp */
#include "source.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void SOURCE::COMPORTEMENT() {
  std::ifstream realStream("in_real.txt");
  std::ifstream imagStream("in_imag.txt");

  float tmp_real, tmp_imag;

  data_valid.write(SC_LOGIC_0);
  data_real.write(0.0);
  data_imag.write(0.0);

  if (!realStream || !imagStream) {
    // cout<<"[SOURCE] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
  }

  wait();

  if (realStream >> tmp_real && imagStream >> tmp_imag) {
    data_real.write(tmp_real);
    data_imag.write(tmp_imag);
    data_valid.write(SC_LOGIC_1);
  }

  while (true) {
    if (data_valid.read() == SC_LOGIC_1 && data_req.read() == SC_LOGIC_1) {
      if (realStream >> tmp_real && imagStream >> tmp_imag) {
        data_real.write(tmp_real);
        data_imag.write(tmp_imag);
        data_valid.write(SC_LOGIC_1);
      } else {
        data_valid.write(SC_LOGIC_0);
      }
    }
    wait();
  }
}
