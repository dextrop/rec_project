
#ifndef PEAKPROCESSING_H
#define PEAKPROCESSING_H

/* @brief : This file handles the processing of fts 
 */

#include <core/datastructure/vecWrapper.h>
#include <core/demodulation/config.h>
#include <core/utils/filters/filter.h>
#include <core/all_config.h>


// @ class : PeakProcessing
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Contains all the functionalities related to peak processing
class PeakProcessing {
public:
    PeakProcessing();
    int FindPeak (vector<double>& peak_vec, double& peak_amp);
    int GetPeakSize();
    int GetBarkerCorrTapsSize();
    void SetCallBack(DebugInfo callback_fun);
private:
    void InitSetup();
    void CreateCarrierSignal();
    std::vector< std::complex<double> > ConvertToPassband(const vector<double>& input_signal);
    void ConvertToPassband (const vector<double>& input_signal, vector<complex<double>> & output_signal);
private:
    int peak_size_;
    RealFilter peak_bpf_;
    RealFilter rrc_filter_;
    RealFilter barker_correlator_;
    vector< complex<double> > carr_signal_;
    DebugInfo debug_info_;
    const FtsParams& fts_params_;
};

#endif
