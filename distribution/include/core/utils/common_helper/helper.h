#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <complex>
#include <iostream>
#include <numeric>
#include <core/utils/filters/filter.h>
#include <core/datastructure/vecWrapper.h>
#include <core/all_config.h>
#include <core/utils/fftwrapper/fftWrapper.h>

#define PI 3.14159265358979

using namespace std;

//new function
void GetArrayMagnitude(FFT_COMPLEX_DATA_TYPE* inputArray, int length , vector<double>& output);

long int getRunTime(long int startMS);

long int getMs();

void getUnitEnergyNormilazionvector(vec &input);

vector<complex<double> > conjVec(vector<complex<double> > &inputVec);

// FFT_COMPLEX_DATA_TYPE* conj(FFT_COMPLEX_DATA_TYPE input);

void conjArray(FFT_COMPLEX_DATA_TYPE *input, FFT_COMPLEX_DATA_TYPE *output, int size);

void Plot(FFT_SCALAR_DATA_TYPE* plotArray, int length, string title);

void Plot_fft(vector<double> &input, string title);

void PlotMagnitude(FFT_COMPLEX_DATA_TYPE* plotArray, int length,string title);

void PlotReal(FFT_COMPLEX_DATA_TYPE* plotArray, int length,string title);

void PlotImag(FFT_COMPLEX_DATA_TYPE* plotArray, int length,string title);

vector<double> getArrayReal(FFT_COMPLEX_DATA_TYPE* inputAsrray, int length);

vector<double> getArrayImag(FFT_COMPLEX_DATA_TYPE* inputArray, int length);

vector<double> getArrayMagnitude(FFT_COMPLEX_DATA_TYPE* inputArray, int length);

vector<double> NormalizeSignal(vector<double> &input);

vector<double> getRealVector(vector<complex<double> > &input);

int calculateErrors(bvec decodedbits , bvec originalbits);

int calculateErrors(bvec decodedbits , bvec originalbits, vec confidenceArray, ivec decodedSymbols);

vector<double> getImagVector(vector<complex<double> > &input);

vector<complex<double> > to_cvec(vector<double> &input);

//vector<complex<double> > elem_mult(vector<complex<double> > &input1, vector<complex<double> > &input2);

void Plot_old(vector<double> &input,string title);
void Plot_old(float* &input,string title, int length);

vector<bool> getBitsFromSymbols(vector<int> &inputVector, int bitsPerSymbol);

vector<int> getSymbolsFromBits(vector<bool> &inputVector, int bitsPerSymbol);

//string getSentDataFromBinaryVector(vector<bool> &input, int numChars);

string decodeBits2String(vector<bool> &input);

//vector<double> fft_fftw(vector<double> &inputSignal, int fftsize);

//vector<double> fft_kiss(vector<double> &inputSignal, int fftsize);

string convertInttoString(int i);

string convertDoubletoString(double i);

string convertBooltoString(bool i);

string convertVectoString(vec input);

string convertIVectoString(ivec input);

int compare(vec data1 , vec data2);

int compareBvec(bvec data1 , bvec data2);

int compareCvec(cvec data1 , cvec data2);

bool validity(string ans);

#if defined LINUX && defined DEBUG
vec getDataFromWav(const char *filepath);
vec getDataFromJson(const char* filename);
#endif



#endif
