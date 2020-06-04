#ifndef KISS_FFT_WRAPPER_H
#define KISS_FFT_WRAPPER_H


#include <core/utils/fftwrapper/kiss_fftr.h>
#include <core/utils/fftwrapper/_kiss_fft_guts.h>

kiss_fftr_cfg kiss_fftr_alloc(int nfft,int inverse_fft,void * mem, size_t * lenmem, kiss_fft_scalar* input, kiss_fft_cpx* output);

kiss_fft_cfg kiss_fft_alloc(int nfft,int inverse_fft,void * mem, size_t * lenmem, kiss_fft_cpx* input, kiss_fft_cpx* output);

#endif
