
#ifndef CTS_DETECTION_H
#define CTS_DETECTION_H

/* @brief : This file handles the data related to cts detection 
 */

#include <core/utils/filters/filter.h>
#include <core/demodulation/helpers/demodHelpers.h>
#include <core/utils/common_helper/helper.h>
#include <vector>
#include <string>

// @ class : CtsDetect 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Contains all the functionalities related to cts detection 
class CtsDetect {

public:
  CtsDetect(bool acknack_state = false);
  bool DetectSamples ( std::vector<double>& audio_samples);
  void SetCallBack(DebugInfo callback_fun);
private:
  bool ProcessPattern ();
  void ResetState ();

private:
  std::string pattern_found_; //101 or 11
  bool cts_detected_;
  int fft_size_;
  int band_start_freq_;
  int band_end_freq_;
  FFT_SCALAR_DATA_TYPE* fft_input_;
  FFT_COMPLEX_DATA_TYPE* fft_output_;
  FFT_CONFIG_REAL fftr_state_;
  std::vector<int> band_freq_;
  DebugInfo debug_info_;
  const CtsParams& cts_params_;

};

#endif
