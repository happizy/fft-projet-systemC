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
		
  float tmp_real, tmp_imag;

  data_valid.write(SC_LOGIC_0);
  data_real.write(0.0);
  data_imag.write(0.0);

  if(!realStream||!imagStream)
    //cout<<"[SOURCE] "<<"Un des fichiers d'entree n'est pas ouvert"<<endl;

  wait();

  realStream>>tmp_real;
  imagStream>>tmp_imag;
  data_real.write(tmp_real);
  data_imag.write(tmp_imag);
  cout << "writing base source values ("<<tmp_real<<", "<<tmp_imag<<") and setting valid" << endl;
  data_valid.write(SC_LOGIC_1);


  wait();

  while(true)
    {
      if(data_req.read() == SC_LOGIC_1){
        if(!realStream.eof()&&!imagStream.eof()){
          realStream>>tmp_real;
          imagStream>>tmp_imag;
          data_real.write(tmp_real);
          data_imag.write(tmp_imag);
          data_valid.write(SC_LOGIC_1);
          //cout << "writing source ("<<tmp_real<<", "<<tmp_imag<<") and setting valid" << endl;
        }else{
          cout << "Fin de fichier input" << endl;
          data_valid.write(SC_LOGIC_0);
        }
      }
      wait();
    }
}	
