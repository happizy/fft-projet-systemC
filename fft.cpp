/* fichier fft.cpp */
#include <systemc.h>
#include "fft.h"

enum data_state {
    INPUT,
    COMPUTE,
    OUTPUT,
    END
};

complex_t twiddles[4] = {
    {1, 0},
    {0.707107, -0.707107},
    {0, -1},
    {-0.707107, -0.707107}
};

void FFT::butterfly(complex_t *p_twiddle, complex_t *p_in1, complex_t *p_in2, complex_t *p_out1, complex_t *p_out2){
    p_out1->real = (p_in1->real + ((p_in2->real * p_twiddle->real) - (p_in2->imag * p_twiddle->imag)));
    p_out1->imag = (p_in1->imag + ((p_in2->real * p_twiddle->imag) + (p_in2->imag * p_twiddle->real)));
    p_out2->real = (p_in1->real - ((p_in2->real * p_twiddle->real) - (p_in2->imag * p_twiddle->imag)));
    p_out2->imag = (p_in1->imag - ((p_in2->real * p_twiddle->imag) + (p_in2->imag * p_twiddle->real)));
}

void FFT::comportement(){
    complex_t cpx_in[N], cpx_out[N], stage1[N], stage2[N];
    enum data_state s = INPUT;

    while(1){
        wait();

        switch(s){
            case INPUT:
                if (data_valid_source.read() == SC_LOGIC_1) {
                    for(size_t i=0; i<N; i++){
                        cpx_in[i].real = real_fifo_source.read();
                        cpx_in[i].imag = imag_fifo_source.read();
                        wait();
                    }
                    s = COMPUTE;
                    wait();
                } else {
                    s = INPUT;
                }
                break;
            case COMPUTE:
                // First stage
                // cout << "Computing stage 1" << endl;
                butterfly(&twiddles[0], &cpx_in[0], &cpx_in[4], &stage1[0], &stage1[1]);
                butterfly(&twiddles[0], &cpx_in[2], &cpx_in[6], &stage1[2], &stage1[3]);
                butterfly(&twiddles[0], &cpx_in[1], &cpx_in[5], &stage1[4], &stage1[5]);
                butterfly(&twiddles[0], &cpx_in[3], &cpx_in[7], &stage1[6], &stage1[7]);

                // Second stage
                // cout << "Computing stage 2" << endl;
                butterfly(&twiddles[0], &stage1[0], &stage1[2], &stage2[0], &stage2[2]);
                butterfly(&twiddles[2], &stage1[1], &stage1[3], &stage2[1], &stage2[3]);
                butterfly(&twiddles[0], &stage1[4], &stage1[6], &stage2[4], &stage2[6]);
                butterfly(&twiddles[2], &stage1[5], &stage1[7], &stage2[5], &stage2[7]);
                            
                // Etape 3
                // cout << "Computing stage 3" << endl;
                butterfly(&twiddles[0], &stage2[0], &stage2[4], &cpx_out[0], &cpx_out[4]);
                butterfly(&twiddles[1], &stage2[1], &stage2[5], &cpx_out[1], &cpx_out[5]);
                butterfly(&twiddles[2], &stage2[2], &stage2[6], &cpx_out[2], &cpx_out[6]);
                butterfly(&twiddles[3], &stage2[3], &stage2[7], &cpx_out[3], &cpx_out[7]);

                s = OUTPUT;
                break;

            case OUTPUT:
                if (data_req_sink.read() == SC_LOGIC_1) {
                    if(real_fifo_sink.num_free() == N && imag_fifo_sink.num_free() == N){
                        for(size_t i=0; i<N; i++){
                            real_fifo_sink.write(cpx_out[i].real);
                            imag_fifo_sink.write(cpx_out[i].imag);
                            wait();
                        }
                        data_valid_sink.write(SC_LOGIC_1);
                        s = END;
                    }
                } else {
                    s = OUTPUT;
                    data_valid_sink.write(SC_LOGIC_0);
                }
                break;
            default:
                
                if (real_fifo_source.num_available() != 0 && imag_fifo_source.num_available() != 0) {
                    s = INPUT;
                    data_req_source.write(SC_LOGIC_1);
                } else {
                    cout << "filter applied." << endl;
                    data_req_source.write(SC_LOGIC_0);
                    s = END;
                }

                break;
        }
    }
}

