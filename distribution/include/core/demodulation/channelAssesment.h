#ifndef CHANNEL_ASSESSMENT_H

#define CHANNEL_ASSESSMENT_H

#include <core/demodulation/config.h>
#include <core/utils/common_helper/helper.h>
#include <core/demodulation/helpers/demodHelpers.h>
//#include <core/demodulation/CTS.h>
#include <core/datastructure/vecWrapper.h>

struct Channel
 {
private:
    FFT_SCALAR_DATA_TYPE* fftInput;
    FFT_COMPLEX_DATA_TYPE* fftOutput;
    FFT_CONFIG_REAL fftr_state;

public:
 	const int calibratingChannel = -1;
 	const int channelBusy = 0;
 	const int channelFree = 1;

    int bandFreq[2] = {17250, 18250};

    int samplesCrossingBand[2] = {16500, 20500};
    int samplesCrossingRefBand[2] = {15000, 16000};
    int samplesCrossingBandGap = 1000;
    int numSamplesCrossingLimit = 15;
    double H = 1.5;


    int fftSize;
 	Channel();
	void setupFFT(int _ffts, int maxPastSamplesInput ,onInfo on_info, onError on_error);
 	void resetChannel();
 	int isChannelFree();
 	void processChunk(vec &chunkData);
	double getMean(vector<double> &inputVector);
	double getStandardDeviation(vector<double> &inputVector, double mean);
	int getSamplesCrossingPattern(vector<double> &FFTmag);
	int getBandRatioPattern(vector<double> &FFTmag);
	int isFound(vector<double> &inputchunk);
	ivec checkChannel(vec &audioSamples);
 	vector<double> audioBuffer;
 	//CTS cts;
 	int processedCount=0;
 	int maxPastSamples = 8;
    int maxSamplesCrossingChunks = 3;
    int maxBandRatioChunks = 2;
 	vector<int> bandRatioIndex, samplesCrossingIndex;
 };
#endif
