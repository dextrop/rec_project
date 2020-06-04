#ifndef DEMOD_CONFIG_H
#define DEMOD_CONFIG_H

#include <core/config.h>


#define CORR_PEAK_RATIO 0.7
#define DOWN_SAMPLING_FACTOR 1
#define DATA_BPF_FFT_SIZE 8192

 #define SYMBOL_TB			 172		// // payload config H=3, 240 with 101 zeros
//#define SYMBOL_TB			 116			// // payload config H=2, 150 with 50 zeros
#define NUM_BIT_PER_SYMBOL 2

#define SAMPLES_WELCH		 SAMPLES_PER_SYMBOL * NUM_PILOT_SYMBOLS
 #define PULSE_RISE_START		 34			// // payload config H=3, 240 with 101 zeros
//#define PULSE_RISE_START		 17			// // payload config H=3, 150 with 50 zeros
#define PULSE_RISE_END			 PULSE_RISE_START + SYMBOL_TB
#define WELCH_POWER_FFT_SIZE 256

#endif