#ifndef FILTER_H
#define FILTER_H 

#include <core/utils/common_helper/helper.h>
#include <complex>
#include <core/utils/fftwrapper/fftWrapper.h>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

class RealFilter{
private:
    FFT_COMPLEX_DATA_TYPE* fftTaps;

    FFT_SCALAR_DATA_TYPE* fftInput;
    FFT_COMPLEX_DATA_TYPE* fftOutput;

    FFT_SCALAR_DATA_TYPE* fftInputTemp;
    FFT_COMPLEX_DATA_TYPE* fftOutputTemp;

    FFT_CONFIG_REAL  fftr_state;
    FFT_CONFIG_REAL  ifftr_state;
    
public:
	RealFilter();
	~RealFilter();

    unsigned int fftSize;
    unsigned int dataSize;
    unsigned int tapsSize;

    bool mode;		//True = Convolve, False = Correlate

	void setupRealFilter(int _ffts,vector<double> &taps, bool filterMode);

	vector<double> convolve(vector<double> &inputSignal);
    vector<double> convolveFromFFT(FFT_COMPLEX_DATA_TYPE* inputSignalFFT);
    FFT_COMPLEX_DATA_TYPE* FFT(vector<double> &inputSignal);
    void freeRealFilter();

};

class ComplexFilter{
private:
    unsigned int fftSize;
    unsigned int dataSize;
    unsigned int tapsSize;

    FFT_COMPLEX_DATA_TYPE* fftTaps;

    FFT_COMPLEX_DATA_TYPE* fftInput;
    FFT_COMPLEX_DATA_TYPE* fftOutput;

    FFT_COMPLEX_DATA_TYPE* fftInputTemp;
    FFT_COMPLEX_DATA_TYPE* fftOutputTemp;

    FFT_CONFIG_COMPLEX  fft_state;
    FFT_CONFIG_COMPLEX  ifft_state;
    
public:
    ComplexFilter();
    ~ComplexFilter();

    bool mode;      //True = Convolve, False = Correlate

    void setupComplexFilter(int _ffts,vector<double> &taps, bool filterMode);

    vector<complex<double> > convolve(vector<complex<double> > &inputSignal);
    void freeComplexFilter();

};

class FFT{
private:
    unsigned int fftSize;

    FFT_SCALAR_DATA_TYPE* fftInput;
    FFT_COMPLEX_DATA_TYPE* fftOutput;

    FFT_CONFIG_REAL  fftr_state;
public:
    FFT();
    ~FFT();
    void setupFFT(int _ffts);
    vector<double> fft(vector<double> &inputSignal);
    void freeFFT();
};

vector<double> rrcFilterGenerator(int span , int ov_fact, double rolloff, int fs);


vector<double> barkerGenerator();

vector<double> IRR_HPF(vector<double> input, int len, float Q,float ratio);
#endif
