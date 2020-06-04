#ifndef FFTW3_WRAPPER_H
#define FFTW3_WRAPPER_H
#include <core/utils/fftwrapper/fftw3.h>
//#include <core/logginlib.h>

fftw_plan fftw_alloc_real(int nfft,int inverse_fft,void * mem, size_t * lenmem, 
									double* input, fftw_complex* output);

fftw_plan fftw_alloc_complex(int nfft,int inverse_fft,void * mem, size_t * lenmem, 
									fftw_complex* input, fftw_complex* output);

void fftw_fft_real(const fftw_plan cfg,const double *timedata,fftw_complex *freqdata);
/*
 input timedata has nfft scalar points
 output freqdata has nfft/2+1 complex points
*/

void fftw_ifft_real(const fftw_plan cfg,const fftw_complex *freqdata,double *timedata);
/*
 input freqdata has  nfft/2+1 complex points
s output timedata has nfft scalar points
*/
void fftw_fft_complex(const fftw_plan cfg,const fftw_complex *timedata,fftw_complex* freqdata);

void fftw_free();
#endif
