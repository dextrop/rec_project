#ifndef MODULATE_H
#define MODULATE_H

/* @brief : This file consists of all the functionalities related to modulation
 */

#include <core/all_config.h>
#include <core/err_crr/fec.h>
#include <core/modulation/payload.h>
#include <core/modulation/modulation_header.h>
#include <core/datastructure/vecWrapper.h>

// @ class : Modulate 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Class depicting the face of modulation 
class Modulate {
  public:
    Modulate();
    void GenerateSignal(const std::string& payload, std::vector<double>& output_signal, bool irr_status = false);
    std::vector<double> GenerateSignal(const std::string& payload, bool irr_status = false);
    void SetCallBack (DebugInfo callback_fun);
    void SetVersion(std::string version_select);
#ifdef DEBUG
    void GetOutputBits(string input, bvec &outputBits);
#endif

  private:
    Fec fec_;
    Payload payload_;
    ModulationHeader header_;
    const FtsParams& fts_params_;
    const PayloadParams& payload_params_;
    DebugInfo debug_info_;
};

#endif
