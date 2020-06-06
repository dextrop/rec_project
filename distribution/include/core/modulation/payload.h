#ifndef MODULATION_PAYLOAD_H
#define MODULATION_PAYLOAD_H

/* @brief : This file consists of all the functionalities related to payload generation 
 */
#include <core/datastructure/vecWrapper.h>
#include <core/modulation/helper/helpers.h>
#include <core/all_config.h>

// @ class : Payload 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Class consisting of all the functionalities related to payload
class Payload {
public:
    Payload();
    std::vector<double> GenerateFreqVec(std::vector<bool>& input_data, bool preamble_add_state = false);
    void GenerateFreqVec (std::vector<bool>& input_data, std::vector<double>& freq_vec, bool preamble_add_state = false); 
    void SetCallBack (DebugInfo callback_fun);
	void InitPayload();
	void SetPayloadParamsExternal(unsigned int flat_region_size, unsigned int num_bit_per_symbol, 
        unsigned int guard_band_zeros, unsigned int payload_fc, unsigned int symbol_data_size, 
        unsigned int symbol_size, unsigned int modulation_index, unsigned int num_data_bands);


private:
    std::vector<double> freq_vec_;
    std::vector<std::vector<double> > symbols_;
    // const PayloadParams& payload_params_;
    PayloadParams& payload_params_;
    DebugInfo debug_info_;
};

#endif // MODULATION_PAYLOAD_H
