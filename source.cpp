/* fichier source.cpp */
#include "source.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


void SOURCE::COMPORTEMENT()
{ 
  std::ifstream realStream("in_real.txt");
  std::ifstream imagStream("in_imag.txt");
		
  float tmp_val_real, tmp_val_imag;

  if(!realStream||!imagStream)
    cout << "[SOURCE] " << "Un des fichiers d'entree n'est pas ouvert" << endl;

  wait();

  while(true) {
    if(!realStream.eof()&&!imagStream.eof()){
      realStream >> tmp_val_real;
      fifo_real.write(tmp_val_real);

      imagStream >> tmp_val_imag;
      fifo_imag.write(tmp_val_imag);
      wait();

      if (fifo_imag.num_free() == 0 && data_req.read() == SC_LOGIC_1) {
        data_valid.write(SC_LOGIC_1);
        cout << "[SOURCE] Data valid (1)" << endl;
      } else { data_valid.write(SC_LOGIC_0); }
    } else { 
      //cout << "[SOURCE] " << "Fin des fichiers d'entree atteinte." << endl;
      wait();
    }
  }
}	
