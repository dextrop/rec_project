#ifndef LIB_TRILL_H
#define LIB_TRILL_H

/* @brief : This file contains the class which is the start of the code execution
 * @todo  : The setup function is not required currently.Need to be changed 
 */

#include <core/global_var.h>
#include <core/responses.h>
#include <core/sdkconfig.h>
#include <core/datastructure/vecWrapper.h>
#include <core/modulation/modulate.h>
#include <core/demodulation/data_handler.h>

// @ class : LibTrill 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1, 2020
// @ brief : Main class exposed to the outside world for starting modulation and demodulation
class LibTrill {

  public :
    LibTrill();//can setup included in libtrill constructor?
    void GetAudioSamples (const std::string& payload, std::vector<double>& output, bool irr_status = false );
    std::vector<double> GetAudioSamples (const std::string& payload, bool irr_status = false );
    CODES Setup (int max_payload_len, int max_past_samples, DATA_TYPE type_sdk);
    void AddBuffer (std::vector<double> audio_buffer);
    std::string ProcessBuffer ();
    std::string GetDecodedString () { return decoded_string_;}
    void SetCallBack (DebugInfo callback_fun);
    void SetVersion(std::string version_select);
    void SetupDemod (int payload_len ,fec_scheme fec_s);
#ifdef DEBUG
    void SetExpectedData(string payload);
#endif
    DemodState GetDemodState ();

  private:
    int max_payload_len_;
    int modulation_output_size_;
    std::string decoded_string_;
    bool sdk_state_;
    Modulate modulate_;
    DataHandler data_handler_;
    DebugInfo debug_info_;
    fec_scheme fec_sch;
};


#endif
