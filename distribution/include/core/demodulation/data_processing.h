#ifndef DATA_PROCESSING_H 
#define DATA_PROCESSING_H 

/* @brief : This file handles the payload related processing 
 * @todo  : Modify the logic for data processing
 */

#include <core/datastructure/vecWrapper.h>
#include <core/utils/filters/filter.h>
#include <core/all_config.h>

extern bvec decodedBits;
extern vec decodedBitsConfidence;
extern ivec decodedSymbols;
extern vector <vector<double>> dataBPFOutput;

// @ class : DataProcessing
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Contains all the functionalities related to payload processing
class DataProcessing {

public:
  DataProcessing();  
  int DataBlockWise();
  void DecodeData();
  double WelchPSD (const std::vector<double>& input_signal, int nper_seg);
  void SetCallBack(DebugInfo callback_fun);
  void SetPayloadParamsExternal(unsigned int flat_region_size, unsigned int num_bit_per_symbol, unsigned int guard_band_zeros,
                                unsigned int payload_fc, unsigned int symbol_data_size, unsigned int symbol_size, 
                                unsigned int modulation_index, unsigned int num_data_bands);

private:
  unsigned num_data_bands_;
  FFT welch_psd_fft_;
  RealFilter temp_data_fft_;
  std::vector<RealFilter> data_bpf_;
  std::vector<double> welch_coefficients_;
  //bool data_processing_complete_;
  //bool second_peak_;
  //bool is_welch_set_;
  PayloadParams& payload_params_;
  // const PayloadParams& payload_params_;
  DebugInfo debug_info_;
  
};   

#endif //DATA_PROCESSING_H
