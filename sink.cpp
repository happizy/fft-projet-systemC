/* fichier sink.cpp */
#include "sink.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void SINK::COMPORTEMENT()
{  
  std::ofstream realStream("out_real.txt");
  std::ofstream imagStream("out_imag.txt");

  std::ifstream realStream_ref("out_real_ref_valid.txt");
  std::ifstream imagStream_ref("out_imag_ref_valid.txt");
		
  float real, imag, real_ref, imag_ref, diff, max_error=0.;
        
  int i;
  if(!realStream||!imagStream||!realStream_ref||!imagStream_ref)
    //cout<<"[SINK] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;
	
  wait();

  while(true) { 
    if (fifo_real.num_available()>=16 && fifo_imag.num_available()>=16) {
      //cout<<"[SINK] "<< "Lecture des 16 �chantillons par le bloc SINK..." << endl;
      for (i = 0; i < N; i++) { 
        real= fifo_real.read();
        imag= fifo_imag.read();
        wait();
        realStream<<real<<endl;
        imagStream<<imag<<endl;
         
        if(!realStream_ref.eof()&&!imagStream_ref.eof()) {
          realStream_ref>>real_ref;
          imagStream_ref>>imag_ref;
          diff=abs(real-real_ref);
          max_error= diff>max_error ? diff : max_error;
          diff=abs(imag-imag_ref);
          max_error= diff>max_error ? diff : max_error;
        }	
      }
      cout<<"[SINK] "<<"Erreur maximale actuelle: "<<max_error<<endl; 
    } else { wait(); } 
  }   
}
