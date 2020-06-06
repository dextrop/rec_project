#ifndef CTS_ACKNACK_H
#define CTS_ACKNACK_H

/* @brief : This file handles the data related to cts detection 
 */

#include <core/utils/filters/filter.h>
#include <core/demodulation/helpers/demodHelpers.h>
#include <core/utils/common_helper/helper.h>
#include <vector>
#include <string>

// @ class : CtsAcknack
// @ author: Phani Sai Chand Gali
// @ Date  : May 12,2020
// @ brief : Contains all the functionalities related to cts acknack detection 
class CtsAcknack {
public:
  CtsAcknack();
  int DetectSamples ( std::vector<double>& audio_samples, std::string payload);
  void SetCallBack(DebugInfo callback_fun);
private:
  int fft_size_;
  int band_start_freq_;
  int band_end_freq_;
  FFT_SCALAR_DATA_TYPE* fft_input_;
  FFT_COMPLEX_DATA_TYPE* fft_output_;
  FFT_CONFIG_REAL fftr_state_;
  DebugInfo debug_info_;
  const CtsParams& cts_params_;
};

#endif
