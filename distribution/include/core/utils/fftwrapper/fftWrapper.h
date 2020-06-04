#ifndef FFT_WRAPPER_H
#define FFT_WRAPPER_H

// #define FFT_MODE_KISS_FFT //newly edited

#ifndef FFT_MODE_KISS_FFT
#define FFT_MODE_FFTW3
#endif

#if defined FFT_MODE_KISS_FFT //newly edited

#include <core/utils/fftwrapper/kissfftWrapper.h>

#define FFT_SCALAR_DATA_TYPE        kiss_fft_scalar
#define FFT_COMPLEX_DATA_TYPE       kiss_fft_cpx
#define FFT_ALLOC_REAL              kiss_fftr_alloc
#define FFT_ALLOC_COMPLEX           kiss_fft_alloc
#define FFT_REAL                    kiss_fftr
#define IFFT_REAL                   kiss_fftri
#define FFT_COMPLEX                 kiss_fft
#define FFT_CONFIG_REAL             kiss_fftr_cfg
#define FFT_CONFIG_COMPLEX          kiss_fft_cfg
#define FFT_FREE                    kiss_fft_free
#define FFT_FREE_PLAN               kiss_fft_free
#define FFT_ALLOC_MEM               malloc


#else // defined FFT_MODE_FFTW3 
#include <core/utils/fftwrapper/fftw3Wrapper.h>

#define FFT_SCALAR_DATA_TYPE        double
#define FFT_COMPLEX_DATA_TYPE       fftw_complex
#define FFT_ALLOC_REAL              fftw_alloc_real
#define FFT_ALLOC_COMPLEX           fftw_alloc_complex
#define FFT_REAL                    fftw_fft_real
#define IFFT_REAL                   fftw_ifft_real
#define FFT_COMPLEX                 fftw_fft_complex
#define FFT_CONFIG_REAL             fftw_plan
#define FFT_CONFIG_COMPLEX          fftw_plan
#define FFT_FREE_PLAN               fftw_destroy_plan
#define FFT_FREE                    fftw_free
#define FFT_ALLOC_MEM               fftw_malloc
#endif

#endif
