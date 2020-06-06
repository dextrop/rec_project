#ifndef FEC_H
#define FEC_H

#include<iostream>
#include <core/global_var.h>
#include <vector>
#include <bitset>
#include <external/liquid/liquidfec/liquid.internal.h>
#include <external/correct/include/fec_shim.h>
// #include <correct.h>
#include <core/global_var_internal.h>


// @ class : Fec
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Class responsible for encoding and decoding of payload
class Fec{

  public:
    Fec();
    std::vector<bool> EncodeData (const std::string& data);
    void EncodeData (const std::string& data, std::vector<bool>& encoded_data); 
    std::string DecodeData (const std::vector<bool>& data,bool& checksum,bool& end_state);
    void SetCallBack (DebugInfo callback_fun); 
    void SetFecScheme(fec_scheme fec_s);
private:
    void LiquidConvEncode (const std::string &input_bytes, fec_scheme fec_s, std::vector<bool>& output_bool_vec);
std::vector<bool> LiquidConvEncode (const std::string &input_bytes, fec_scheme fec_s);
    std::string LiquidConvDecode (int n, const std::vector<bool>& demodulate_bits, fec_scheme fec_s, bool &checksum, bool& end_state);
    void ConvertUcharToBits(unsigned char* data_input, int data_size, std::vector<bool>& output);
    void ConvertBitsToUchar ( const std::vector<bool>& bits, unsigned char* data_output, int data_size);

	std::vector<bool> convertUcharToBits(unsigned char* dataInput,int size);

private:
    fec_scheme fec_scheme_;
    crc_scheme crc_scheme_;
    DebugInfo debug_info_;
};

#endif /* FEC_H */
