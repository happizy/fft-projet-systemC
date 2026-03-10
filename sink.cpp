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
  data_req.write(SC_LOGIC_0);
  int i;
  if (!realStream || !imagStream || !realStream_ref || !imagStream_ref) {
    // cout<<"[SINK] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
  }
  wait(2);

  while (true) {
    // if (in.num_available() == 16 && data_valid.read() == SC_LOGIC_1) {
    //  cout<<"[SINK] "<< "Lecture des 16 �chantillons par le bloc SINK..." <<
    //  endl;
    data_req.write(SC_LOGIC_0);
    if (n < SIZE) {
      if (data_valid.read() == SC_LOGIC_1) {
        real = data_real.read();
        imag = data_imag.read();
        realStream << real << endl;
        imagStream << imag << endl;
        n++;
      }
      if (n < SIZE - 1) {
        data_req.write(SC_LOGIC_1);
      }
    } else {
      n = 0;
    }
    wait();

    //   for (i = 0; i < 8; i++)
    //     {
    //       real= in.read();
    // 	wait();
    //       imag= in.read();
    // 	wait();
    //       realStream<<real<<endl;
    //       imagStream<<imag<<endl;

    //           if(!realStream_ref.eof()&&!imagStream_ref.eof()){
    // 	realStream_ref>>real_ref;
    // 	imagStream_ref>>imag_ref;
    // 	diff=abs(real-real_ref);
    // 	max_error= diff>max_error ? diff : max_error;
    // 	diff=abs(imag-imag_ref);
    // 	max_error= diff>max_error ? diff : max_error;
    // 	}
    //}
    // cout<<"[SINK] "<<"Erreur maximale actuelle: "<<max_error<<endl;
  }
  //   else {
  //     wait();
  //   }
}
