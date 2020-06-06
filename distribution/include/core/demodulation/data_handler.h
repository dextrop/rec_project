#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <core/demodulation/cts_detection.h>
#include <core/demodulation/cts_acknack.h>
#include <core/demodulation/peak_processing.h>
#include <core/demodulation/data_processing.h>
#include <core/err_crr/fec.h>
#include <core/all_config.h>

/* @brief : This file handles the data recieved from microphone 
 * @todo  : Modify the ProcessData function
 */

#define PEAKCHECKS 4
extern std::vector<bool> decodedBits;
extern std::vector<double> decodedBitsConfidence;
extern std::vector<int> decodedSymbols;
extern std::string gModPayload;
  /*
class DemodState;

class DataHandler {

  public:
    void ProcessBuffer (vector<double>& v);
  private:
    void ChangeState (DemodState* state);
  private:
    DemodState* state_;
    friend class DemodState;
};

class DemodState {

  public:
    virtual void ProcessBuffer (DataHandler* data_handler, vector<double>&v);
  protected:
    void ChangeState (DataHandler* data_handler, DemodState* state);
};
*/

// @ class : DemodState
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Contains all states related to demodulation 
enum class DemodState {
  INIT_STATE,
  CTS_DETECTED,
  FTS_DETECTED,
  DATA_DETECTED
};

// @ class : DataHandler 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Class that handler the data coming from microphone
class DataHandler {
public:
    DataHandler();
    void Reset();
    void AddBuffer(const std::vector<double>& buffer);
    void ProcessChunk();
    int ProcessAcknack(); //processing acknack
    std::string GetDecodedString ();
    DemodState GetCurrentState();
    void SetCallBack(DebugInfo callback_fun);
    void SetVersion (std::string version_select);
#ifdef DEBUG
    std::vector<bool> expected_bits;
#endif
    void ProcessCts(); 
    void ProcessFts(); 
    void ProcessData(); 

private:

    //@todo add it to global variables
  int checkstatus = 0;
  int peakIndex[PEAKCHECKS];
  double peakAmp[PEAKCHECKS] = {0,0,0,0};
  bool is_processing_; //didn't find the use of this variable
  DemodState current_state_;
  CtsDetect cts_detect_; //detecting cts
  DataProcessing data_processing_; //data processing
  PeakProcessing peak_processing_; //peak processing in fts detection
  int fts_counter_; //for skipping
  int counter_;
  Fec fec_;
  std::string decoded_payload_; //decoded payload
  DebugInfo debug_info_; //for printing the debug information into the callback
  CtsParams& cts_params_; //reference to cts parameters
  FtsParams& fts_params_; //reference to fts parameters
  PayloadParams& payload_params_; //reference to payload parameters
  int cts_samples_count_; //no of chunks of cts processed from first figuring of cts
};

#endif
