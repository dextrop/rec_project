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
// @ Date  : Apr 1,2020
// @ brief : Main class exposed to the outside world for starting modulation and demodulation
class LibTrill {

  public :
    LibTrill();//can setup included in libtrill constructor?
    void GetAudioSamples (const std::string& payload, std::vector<double>& output, bool is_acknack_mode = false );
    std::vector<double> GetAudioSamples (const std::string& payload, bool is_acknack_mode = false );
    bool Setup (int payload_len);
    void AddBuffer (std::vector<double> audio_buffer);
    int ProcessBuffer ();
    std::string GetDecodedString ();
    void ResetDecodedString();
    void SetCallBack (DebugInfo callback_fun);
    void Reset();
    //void SetVersion(std::string version_select);
    //void SetupDemod (int payload_len ,fec_scheme fec_s);
    int ProcessAcknack();
#ifdef DEBUG
    void SetExpectedData(string payload);
#endif
    DemodState GetDemodState ();

  private:
    void SetVersion(std::string version_select);
  private:
    int max_payload_len_;//max payload length our code supports
    int payload_len_;//determines the payload length in modulation as well as demodulation
    bool sdk_state_; // represents whether SDK is setup or not
    Modulate modulate_; //modulation member
    DataHandler data_handler_; //demodulation member
    DebugInfo debug_info_;//member for callbacks
    fec_scheme fec_sch_;//currently supporting a single fec scheme
};


#endif
