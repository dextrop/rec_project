
/*
 * coreconfig.h //contaings configs for core MTFSK module
 *
 *  Created on: 3-Oct-2019
 *      Author: vineeth
 */


#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_
#include <string>
#include <iostream>
#include <cmath>
#include <core/logginlib.h>
#include <core/all_config.h>

typedef void (*onInfo) (string data);
typedef void (*onError) (string message, int code);


#define PI 3.14159265358979

using namespace std;

#define FS44K



#ifdef FS44K
/*
* Config for 44100 Sample Rate
*/

#define FS 44100
enum CTS_FREQ_ARR{
    CTS_FREQ_1 = 17250,
    CTS_FREQ_2 = 18250,
};
#define ONEWAY_COMMUNICATION 1
#define TWOWAY_COMMUNICATION 2
#define  COMMUNICATION_MODE TWOWAY_COMMUNICATION
// Preamble and RRC Config
#define PREAMBLE_STATE false
#define MULTIPLEBLOCKS false

#if PREAMBLE_STATE
#define PREAMBLE_SYMBOL_COUNT 32
#else
#define PREAMBLE_SYMBOL_COUNT 0
#endif



typedef struct config{
    int ov_fact  = 40;
    double rrc_span = 10.0;
    int barkerLength = 13;
    int berkerSampleSize = ov_fact*(barkerLength+1) - 1;
    int max_value = ov_fact*(barkerLength+1)-1 > rrc_span*ov_fact + 1?ov_fact*(barkerLength+1)-1:rrc_span*ov_fact + 1;
    int powFactor = (log(2*max_value+1)/log(2)) + 1;
    int fftSizeForFts = pow(2,powFactor);
    int rrcFFTsize 	= fftSizeForFts;
    int peakBpfFFTsize = fftSizeForFts;
    int  barkerFFTsize = fftSizeForFts;
    double roll_off = 0.25;
    int barkerZeros = 4000;

    int peakToData  = barkerZeros + (berkerSampleSize/2);
    double peakThreshold = (10.0/559.0)*berkerSampleSize;
//#define PEAK_THRESHOLD 270.0/559

    // payload config H=3, 240 with 101 zeros
     int guardbandZeros =  101;
     int payloadSymbolDataSize = 240;
     int payloadSymbolSize = 341;
     int payloadFlatRegionSize =  172;
     double modulationIndex = 3.;

    // payload config H=3, 150 with 50 zeros
    //    int guardbandZeros =  50;
    //    int payloadSymbolDataSize = 150;
    //    int payloadSymbolSize = 200;
    //    int payloadFlatRegionSize = 116;
    //    double modulationIndex = 2.;
    double delf =  modulationIndex*FS/(payloadFlatRegionSize*2);
    int  dataFc = 17500;
    int ftsFC = 17000;
//    void set(){
//        berkerSampleSize = ov_fact*(barkerLength+1) - 1;
//        max_value = ov_fact*(barkerLength+1)-1 > rrc_span*ov_fact + 1?ov_fact*(barkerLength+1)-1:rrc_span*ov_fact + 1;
//        powFactor = log2(2*max_value+1) + 1;
//        fftSizeForFts = pow(2,powFactor);
//        rrcFFTsize 	= fftSizeForFts;
//        peakBpfFFTsize = fftSizeForFts;
//        barkerFFTsize = fftSizeForFts;
//        roll_off = 0.25;
//        peakToData  = barkerZeros + (berkerSampleSize/2);
//        peakThreshold = (270.0/559.0)*berkerSampleSize;
//
//        // payload config H=3, 240 with 101 zeros
//        if(modulationIndex == 3.) {
//            guardbandZeros = 101;
//            payloadSymbolDataSize = 240;
//            payloadSymbolSize = 341;
//            payloadFlatRegionSize = 172;
//        }
//        else if(modulationIndex == 2.) {
//            guardbandZeros =  50;
//            payloadSymbolDataSize = 150;
//            payloadSymbolSize = 200;
//            payloadFlatRegionSize = 116;
//        }
//        delf =  modulationIndex*FS/(payloadFlatRegionSize*2);
//    }

} CONFIG;

extern CONFIG setUpConfig;


#define DATA_NUM_BANDS 8
//#define RRC_FILTER_FFT_SIZE 	2048
//#define PEAK_BPF_FFT_SIZE 	    2048
//#define BARKER_CORR_FFT_SIZE 	2048
//
//#define RRC_OV_FACT 40
//#define RRC_ROLLOFF 0.25
//#define RRC_SPAN 10
//
// payload config
//#define PAYLOAD_GAURD_BAND_SIZE 101
//#define PAYLOAD_SYMBOL_SIZE 240
//#define SAMPLES_PER_SYMBOL 341
//#define PAYLOAD_FLAT_REGION_SIZE 172
//#define MODULATION_INDEX	 3.
//#define DELF 				 MODULATION_INDEX*FS/(PAYLOAD_FLAT_REGION_SIZE*2)
//#define FC_DATA 17500
//agmlejuukwcibxubumen
//wdvmxxrdryxlmndqtukw

// filters config
#define FILTER_PI (3.141592653589793238462643)
#define BIQUAD_MIN_RATIO     (0.000001)
#define BIQUAD_MIN_Q (0.00001)
#define RS_CONFIG_FACTOR 1
//#define DATA_NUM_BANDS 8

#define FTS_REPEAT_FREQUENCY 2
#define CTS_REPEAT_FREQUENCY 2

#if RS_CONFIG_FACTOR == 1
    #define CHAR_UNITS_PERBLOCK  10
//    #define DIGIT_UNITS_PERBLOCK 21
    #define DIGIT_UNITS_PERBLOCK 25
    #define ALPHANUMERIC_UNITS_PERBLOCK 14
    #define DATABITS_LENGTH 90
    #define RS_ERROR_PARITY 11
#elif RS_CONFIG_FACTOR == 2
    #define CHAR_UNITS_PERBLOCK 8
//    #define DIGIT_UNITS_PERBLOCK 16
    #define DIGIT_UNITS_PERBLOCK 19
    #define ALPHANUMERIC_UNITS_PERBLOCK 10
    #define DATABITS_LENGTH 70
    #define RS_ERROR_PARITY 12
#else
    #define CHAR_UNITS_PERBLOCK 5
//    #define DIGIT_UNITS_PERBLOCK 11
    #define DIGIT_UNITS_PERBLOCK 13
    #define ALPHANUMERIC_UNITS_PERBLOCK 7
    #define DATABITS_LENGTH 50
    #define RS_ERROR_PARITY 13
#endif


#endif // FS44K
#endif //HEADER

