/* fichier fft.cpp */
#include "fft.h"
#include <systemc.h>

enum data_state { INPUT, COMPUTE, OUTPUT, END };

twiddle_t twiddles[4] = {
    {1, 0}, {0.707107, -0.707107}, {0, -1}, {-0.707107, -0.707107}};

void FFT::comportement() {
  int n = 0;
  int m = 0;
  complex_t<0> cpx_in[SIZE];
  complex_t<1> stage1[SIZE];
  complex_t<2> stage2[SIZE];
  complex_t<3> cpx_out[SIZE];
  enum data_state s = INPUT;
  data_req_source.write(SC_LOGIC_0);
  data_valid_sink.write(SC_LOGIC_0);
  wait(15);
  while (1) {
    wait();
    switch (s) {
    case INPUT:
      data_req_source.write(SC_LOGIC_1);
      if (data_valid_source.read() == SC_LOGIC_1) {
        cpx_in[n].real = data_real_in.read();
        cpx_in[n].imag = data_imag_in.read();
        n++;
        if (n >= SIZE) {
          data_req_source.write(SC_LOGIC_0);
          n = 0;
          s = COMPUTE;
        }
      }
      break;

    case COMPUTE:
      cout << "Values loaded in fft :" << endl;
      cout << "(" << cpx_in[0].real << ", " << cpx_in[0].imag << ")" << endl;
      cout << "(" << cpx_in[1].real << ", " << cpx_in[1].imag << ")" << endl;
      cout << "(" << cpx_in[2].real << ", " << cpx_in[2].imag << ")" << endl;
      cout << "(" << cpx_in[3].real << ", " << cpx_in[3].imag << ")" << endl;
      cout << "(" << cpx_in[4].real << ", " << cpx_in[4].imag << ")" << endl;
      cout << "(" << cpx_in[5].real << ", " << cpx_in[5].imag << ")" << endl;
      cout << "(" << cpx_in[6].real << ", " << cpx_in[6].imag << ")" << endl;
      cout << "(" << cpx_in[7].real << ", " << cpx_in[7].imag << ")" << endl;
      // First stage
      // cout << "COMPUTE:" << endl;
      cout << "Computing stage 1" << endl;
      butterfly(&twiddles[0], &cpx_in[0], &cpx_in[4], &stage1[0], &stage1[1]);
      butterfly(&twiddles[0], &cpx_in[2], &cpx_in[6], &stage1[2], &stage1[3]);
      butterfly(&twiddles[0], &cpx_in[1], &cpx_in[5], &stage1[4], &stage1[5]);
      butterfly(&twiddles[0], &cpx_in[3], &cpx_in[7], &stage1[6], &stage1[7]);
      //   printf("stage1[0](%f)(%f)\r\n", stage1[0].real, stage1[0].imag);
      //   printf("stage1[1](%f)(%f)\r\n", stage1[1].real, stage1[1].imag);
      //   printf("stage1[2](%f)(%f)\r\n", stage1[2].real, stage1[2].imag);
      //   printf("stage1[3](%f)(%f)\r\n", stage1[3].real, stage1[3].imag);
      //   printf("stage1[4](%f)(%f)\r\n", stage1[4].real, stage1[4].imag);
      //   printf("stage1[5](%f)(%f)\r\n", stage1[5].real, stage1[5].imag);
      //   printf("stage1[6](%f)(%f)\r\n", stage1[6].real, stage1[6].imag);
      //   printf("stage1[7](%f)(%f)\r\n", stage1[7].real, stage1[7].imag);

      // Second stage
      cout << "Computing stage 2" << endl;
      butterfly(&twiddles[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
      butterfly(&twiddles[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
      butterfly(&twiddles[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
      butterfly(&twiddles[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);
      //   printf("stage2[0](%f)(%f)\r\n", stage2[0].real, stage2[0].imag);
      //   printf("stage2[1](%f)(%f)\r\n", stage2[1].real, stage2[1].imag);
      //   printf("stage2[2](%f)(%f)\r\n", stage2[2].real, stage2[2].imag);
      //   printf("stage2[3](%f)(%f)\r\n", stage2[3].real, stage2[3].imag);
      //   printf("stage2[4](%f)(%f)\r\n", stage2[4].real, stage2[4].imag);
      //   printf("stage2[5](%f)(%f)\r\n", stage2[5].real, stage2[5].imag);
      //   printf("stage2[6](%f)(%f)\r\n", stage2[6].real, stage2[6].imag);
      //   printf("stage2[7](%f)(%f)\r\n", stage2[7].real, stage2[7].imag);

      // Etape 3
      cout << "Computing stage 3" << endl;
      butterfly(&twiddles[0], &stage2[0], &stage2[4], &cpx_out[0], &cpx_out[4]);
      butterfly(&twiddles[1], &stage2[1], &stage2[5], &cpx_out[1], &cpx_out[5]);
      butterfly(&twiddles[2], &stage2[2], &stage2[6], &cpx_out[2], &cpx_out[6]);
      butterfly(&twiddles[3], &stage2[3], &stage2[7], &cpx_out[3], &cpx_out[7]);

      //   cout << "------ FFT done, Values ----------------------------" <<
      //   endl; printf("cpx_out[0](%8f)(%8f)\r\n", cpx_out[0].real,
      //   cpx_out[0].imag); printf("cpx_out[1](%8f)(%8f)\r\n", cpx_out[1].real,
      //   cpx_out[1].imag); printf("cpx_out[2](%8f)(%8f)\r\n", cpx_out[2].real,
      //   cpx_out[2].imag); printf("cpx_out[3](%8f)(%8f)\r\n", cpx_out[3].real,
      //   cpx_out[3].imag); printf("cpx_out[4](%8f)(%8f)\r\n", cpx_out[4].real,
      //   cpx_out[4].imag); printf("cpx_out[5](%8f)(%8f)\r\n", cpx_out[5].real,
      //   cpx_out[5].imag); printf("cpx_out[6](%8f)(%8f)\r\n", cpx_out[6].real,
      //   cpx_out[6].imag); printf("cpx_out[7](%8f)(%8f)\r\n", cpx_out[7].real,
      //   cpx_out[7].imag);

      m = 0;
      s = OUTPUT;
      break;

    case OUTPUT:
      if (m < SIZE) {
        data_real_out.write(cpx_out[m].real);
        data_imag_out.write(cpx_out[m].imag);
        data_valid_sink.write(SC_LOGIC_1);
        cout << "(" << cpx_out[m].real << "," << cpx_out[m].imag << ")" << endl;
        m++;
      } else {
        cout << "FFT output done" << endl;
        data_valid_sink.write(SC_LOGIC_0);
        data_req_source.write(SC_LOGIC_1);
        cout << "Work done 🍻" << endl;
        s = INPUT;
      }
      break;
    default:
      break;
    }
  }
}
