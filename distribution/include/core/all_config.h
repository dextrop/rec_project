#ifndef ALL_CONFIG_H
#define ALL_CONFIG_H

/* @brief : Currently rapidjson code is commented. But will be enabled 
 *          in the development code.
 *          This file contains all the information related to CTS,FTS
 *          and Payload parameters.
 * @todo  : Find Whether to use these classes or directly macros.
 */

/*
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
*/

#include <iostream>
#include <cmath>
#include <core/responses.h>
#include <core/config.h>
#include <vector>
#include <core/global_var_internal.h>

#define FS 44100
using namespace std;

//using namespace rapidjson;


// @ class : CtsParams
// @ author: Phani Sai Chand Gali
// @ Date  : Jan 31,2020
// @ brief : Class containing all the modulation parameters
class CtsParams {
  public:
    CtsParams () :
      block_size_ (2048),
      gap_size_ (1024),
      bands_ (2),
      repeat_freq_(2),
      first_freq_ (17250),
      second_freq_ (18250),
      fft_size_ (1024),
      acknack_fft_size_ (2048),
      band_start_ (17000),
      band_end_ (19500),
      band_energy_gap_ (500),
      acknack_band_gap_(100),
      acknack_dominant_freq_window_(100),
      dominant_freq_window_ (200),
      pattern_match_size_ (3),
      acknack_pattern_match_size_(2),
      false_return_ (-10),
      band_ratio_limit_ (0.6),
      sine_amp_ (1.0),
      flat_region_percent_ (40)
      {};

    //setters
    void SetBlockSize(unsigned block_size) { block_size_ = block_size; }
    void SetGapSize(unsigned gap_size) { gap_size_ = gap_size; }
    void SetNumberOfBands(unsigned no_of_bands) { bands_ = no_of_bands; }
    void SetRepeatFrequency(unsigned repeat_frequency) { repeat_freq_ = repeat_frequency; }
    void SetFirstFrequency(int first_frequency) { first_freq_ = first_frequency; }
    void SetSecondFrequency(int second_frequency) { second_freq_ = second_frequency; }
    void SetFFTSize (unsigned fft_size) { fft_size_ = fft_size; }
    void SetAcknackFFTSize (unsigned acknack_fft_size) { acknack_fft_size_ = acknack_fft_size; }
    void SetBandStart (unsigned band_start) { band_start_ = band_start; }
    void SetBandEnd (unsigned band_end) { band_end_ = band_end; }
    void SetBandEnergyGap (unsigned band_energy_gap) { band_energy_gap_ = band_energy_gap; }
    void SetAcknackBandGap(int acknack_band_gap) { acknack_band_gap_ = acknack_band_gap; }
    void SetDominantFreqWindow(unsigned dominant_freq_window) { dominant_freq_window_ = dominant_freq_window; }
    void SetAcknackDominantFreqWindow(unsigned acknack_dominant_freq_window) { acknack_dominant_freq_window_ = acknack_dominant_freq_window; }
    void SetPatternMatchSize (unsigned pattern_match_size) { pattern_match_size_ = pattern_match_size; }
    void SetAckNackPatternMatchSize (unsigned pattern_match_size) { acknack_pattern_match_size_ = pattern_match_size; }
    void SetFalseReturn (int false_return) { false_return_ = false_return; }
    void SetBandRatioLimit (double band_ratio_limit) { band_ratio_limit_ = band_ratio_limit; }
    void SetSineAmp(double sine_amp) { sine_amp_ = sine_amp; }
    void SetFlatRegionPercent(unsigned flat_region_percent) { flat_region_percent_ = flat_region_percent; }
    //getters
    unsigned GetBlockSize () const { return block_size_; }
    unsigned GetGapSize () const { return gap_size_; }
    unsigned GetNumberOfBands () const { return bands_; }
    unsigned GetRepeatFrequency () const { return repeat_freq_; }
    int GetFirstFrequency () const { return first_freq_; }
    int GetSecondFrequency () const { return second_freq_; }
    unsigned GetFFTSize () const { return fft_size_; }
    int GetAcknackFFTSize () const { return acknack_fft_size_; }
    unsigned GetBandStart () const { return band_start_; }
    unsigned GetBandEnd () const { return band_end_; }
    unsigned GetBandEnergyGap () const { return band_energy_gap_; }
    unsigned GetAcknackBandGap () const { return acknack_band_gap_; }
    unsigned GetDominantFrequencyWindow () const { return dominant_freq_window_; }
    int GetAcknackDominantFreqWindow () const { return acknack_dominant_freq_window_; }
    unsigned GetPatternMatchSize () const { return pattern_match_size_; }
    unsigned GetAckNackPatternMatchSize () const { return acknack_pattern_match_size_; }
    int GetFalseReturn () const { return false_return_; }
    double GetBandRatioLimit () const { return band_ratio_limit_; }
    double GetSineAmp () const { return sine_amp_; }
    double GetFlatRegionPercent () const { return flat_region_percent_; }

    /*
    void DeSerialize (const Value& d); 

    template <typename Writer>
    void Serialize(Writer& writer) const 
    {
    
      writer.StartObject();
    
      writer.Key("block_size");
      writer.Uint(block_size_);
    
      writer.Key("gap_size");
      writer.Uint(gap_size_);
    
      writer.Key("no_of_bands");
      writer.Uint(bands_);
    
      writer.Key("repeat_frequency");
      writer.Uint(repeat_freq_);
    
      writer.Key("first_frequency");
      writer.Int(first_freq_);
    
      writer.Key("second_freqency");
      writer.Int(second_freq_);
    
      writer.Key("fft_size");
      writer.Uint(fft_size_);
    
      writer.Key("band_start_frequency");
      writer.Uint(band_start_);
    
      writer.Key("band_end_frequency");
      writer.Uint(band_end_);
    
      writer.Key("band_energy_gap");
      writer.Uint(band_energy_gap_);
    
      writer.Key("dominant_frequency_window");
      writer.Uint(dominant_freq_window_);
    
      writer.Key("pattern_match_size");
      writer.Uint(pattern_match_size_);
    
      writer.Key("acknack_pattern_match_size");
      writer.Uint(acknack_pattern_match_size_);
    
      writer.Key("false_return");
      writer.Int(false_return_);
    
      writer.Key("band_ratio_limit");
      writer.Double(band_ratio_limit_);
    
      writer.Key("sine_amplitude");
      writer.Double(sine_amp_);
    
      writer.Key("flat_region_percent");
      writer.Double(flat_region_percent_);
    
      writer.EndObject();
    }
    */

  private:
    unsigned block_size_;
    unsigned gap_size_;
    unsigned bands_;
    unsigned repeat_freq_;
    int first_freq_;
    int second_freq_;
    unsigned fft_size_;
    int acknack_fft_size_;
    unsigned band_start_;
    unsigned band_end_;
    unsigned band_energy_gap_; 
    int acknack_band_gap_; 
    unsigned dominant_freq_window_;
    int acknack_dominant_freq_window_;
    unsigned pattern_match_size_;
    unsigned acknack_pattern_match_size_;
    int false_return_; 
    double   band_ratio_limit_;
    double   sine_amp_;
    double   flat_region_percent_;
};

// @ class : payLoadParams 
// @ author: Phani Sai Chand Gali
// @ Date  : Jan 31,2020
// @ brief : Class containing all the payload related parameters
class PayloadParams {
  public:
    PayloadParams() :
      data_bpf_fft_size_ (8192),
      symbol_tb_ (172),
      num_bit_per_symbol_ (2),
      pulse_rise_start_ (34),
      guard_band_zeros_ (101),
      symbol_data_size_ (240),
      symbol_size_ (341),
      flat_region_size_ (172),
      welch_power_fft_size_ (256),
      modulation_index_ (3),
      multiple_blocks_ (false),
      preamble_state_ (false),
      preamble_symbol_count_ (0),
      num_data_bands_ (8),
      max_payload_length_ (50),
      payload_amp_ (1.0),
      payload_carrier_freq_ (17500)
      { 
        SetParameters();
      }

    //setters
    void SetDataBPFFFTSize (unsigned data_bpf_fft_size) { data_bpf_fft_size_ = data_bpf_fft_size; }
    void SetSymbolTB (unsigned symbol_tb) { symbol_tb_ = symbol_tb; }
    void SetNumBitPerSymbol (unsigned num_bit_per_symbol) { num_bit_per_symbol_ = num_bit_per_symbol; }
    void SetPulseRiseStart(unsigned pulse_raise_start) { pulse_rise_start_ = pulse_raise_start; }
    void SetGuardBandZeros (unsigned guard_band_zeros) { guard_band_zeros_ = guard_band_zeros; }
    void SetSymbolDataSize (unsigned symbol_data_size) { symbol_data_size_ = symbol_data_size; }
    void SetSymbolSize (unsigned symbol_size) { symbol_size_ = symbol_size; }
    void SetFlatRegionSize (unsigned flat_region_size) { flat_region_size_ = flat_region_size; }
    void SetWelchPowerFFTSize (unsigned welch_power_fft_size) { welch_power_fft_size_ = welch_power_fft_size; }
    void SetModulationIndex (unsigned modulation_index) { modulation_index_ = modulation_index; }
    void SetMultipleBlocks (bool multiple_blocks) { multiple_blocks_ = multiple_blocks; }
    void SetPreambleState (bool preamble_state) { preamble_state_ = preamble_state; }
    void SetPreambleSymbolCount (unsigned preamble_symbol_count) { preamble_symbol_count_ = preamble_symbol_count; }
    void SetNumDataBands (unsigned no_of_bands) { num_data_bands_ = no_of_bands; }
    void SetMaxPayloadLength (unsigned max_payload_length) { max_payload_length_ = max_payload_length; }
    void SetPayloadCarrierFrequency(unsigned payload_carrier_freq) { payload_carrier_freq_ = payload_carrier_freq; }
    void SetPayloadAmp (double payload_amp) { payload_amp_ = payload_amp; }
    //getters
    unsigned GetDataBPFFFTSize() const { return data_bpf_fft_size_; }
    unsigned GetSymbolTB () const { return symbol_tb_; }
    unsigned GetNumBitPerSymbol () const { return num_bit_per_symbol_; }
    unsigned GetPulseRiseStart () const { return pulse_rise_start_; }
    unsigned GetPulseRiseEnd () const { return (pulse_rise_start_ + symbol_tb_); }
    unsigned GetGuardBandZeros () const { return guard_band_zeros_; }
    unsigned GetSymbolDataSize () const { return symbol_data_size_; }
    unsigned GetSymbolSize () const { return symbol_size_; }
    unsigned GetFlatRegionSize () const { return flat_region_size_; }
    unsigned GetWelchPowerFFTSize () const { return welch_power_fft_size_; }
    unsigned GetModulationIndex () const { return modulation_index_; }
    bool GetMultipleBlocks () const { return multiple_blocks_; }
    bool GetPreambleState () const { return preamble_state_; }
    unsigned GetPreambleSymbolCount () const { return preamble_symbol_count_; }
    unsigned GetNumDataBands() const { return num_data_bands_; }
    unsigned GetMaxPayloadLength() const { return max_payload_length_; }
    unsigned GetPayloadCarrierFrequency() const { return payload_carrier_freq_; }
    double GetDeltaFrequency() const { return delta_freq_; }
    double GetPayloadAmp () const { return payload_amp_; }

    /*
    void DeSerialize (const Value& d); 

    template <typename Writer>
    void Serialize(Writer& writer) const 
    {
    
      writer.StartObject();
    
      writer.Key("data_bpf_fft_size");
      writer.Uint(data_bpf_fft_size_);
    
      writer.Key("symbol_tb");
      writer.Uint(symbol_tb_);
    
      writer.Key("num_bit_per_symbol");
      writer.Uint(num_bit_per_symbol_);
    
      writer.Key("pulse_rise_start");
      writer.Uint(pulse_rise_start_);
    
      writer.Key("guard_band_zeros");
      writer.Uint(guard_band_zeros_);
    
      writer.Key("symbol_data_size");
      writer.Uint(symbol_data_size_);
    
      writer.Key("symbol_size");
      writer.Uint(symbol_size_);
    
      writer.Key("flat_region_size");
      writer.Uint(flat_region_size_);
    
      writer.Key("welch_power_fft_size");
      writer.Uint(welch_power_fft_size_);
    
      writer.Key("modulation_index");
      writer.Uint(modulation_index_);
    
      writer.Key("multiple_blocks");
      writer.Bool(multiple_blocks_);
    
      writer.Key("preamble_state");
      writer.Bool(preamble_state_);
    
      writer.Key("preamble_symbol_count");
      writer.Uint(preamble_symbol_count_);
    
      writer.Key("no_of_data_bands");
      writer.Uint(num_data_bands_);
    
      writer.Key("max_payload_length");
      writer.Uint(max_payload_length_);
    
      writer.Key("payload_carrier_frequency");
      writer.Uint(payload_carrier_freq_);
    
      writer.Key("pay_load_amplitude");
      writer.Double(payload_amp_);
    
      writer.EndObject();
    
    }
    */

  private:
    void SetParameters();
  private:
    unsigned data_bpf_fft_size_;
    unsigned symbol_tb_;
    unsigned num_bit_per_symbol_;
    unsigned pulse_rise_start_;
    unsigned guard_band_zeros_;
    unsigned symbol_data_size_;
    unsigned symbol_size_;
    unsigned flat_region_size_;
    unsigned welch_power_fft_size_;
    unsigned modulation_index_;
    bool multiple_blocks_;
    bool preamble_state_;
    unsigned preamble_symbol_count_;
    unsigned num_data_bands_;
    unsigned max_payload_length_;
    unsigned payload_carrier_freq_;
    double delta_freq_;
    double payload_amp_;
};

// @ class : ftsParams 
// @ author: Phani Sai Chand Gali
// @ Date  : Jan 31,2020
// @ brief : Class containing all the fine time synchronization (fts) related parameters
class FtsParams {
	public:
    FtsParams() :
      ov_fact_ (40),
      rrc_span_ (10.0),
      barker_length_ (13),
      roll_off_ (0.25),
      barker_zeros_ (4000),
      down_sampling_factor_ (1),
      fts_amp_ (4.0),
      repeat_freq_(2),
      peak_checks_ (3),
      fts_carrier_freq_ (17000),
      cork_peak_ratio_ (0.7)
    {
      SetParameters();
    } 

    //setters
    //void setOvFact (unsigned ov_fact) { ovFact = ov_fact; }
    //void setRrcSpan(double rrc_span) { rrcSpan = rrc_span; }
    //void setBarkerLength (unsigned barker_length) { barkerLength = barker_length; } 
    void SetRollOff (double roll_off) { roll_off_ = roll_off; }
    //void setBarkerZeros (unsigned barker_zeros) { barkerZeros = barker_zeros; }
    void SetDownSamplingFactor (unsigned down_sampling_factor) { down_sampling_factor_ = down_sampling_factor; }
    void SetFTSCarrierFrequency(unsigned fts_carrier_freq) { fts_carrier_freq_ = fts_carrier_freq; }
    void SetFTSAmp(double fts_amp) { fts_amp_ = fts_amp; }
    void SetCorkPeakRatio (double cork_peak_ratio) { cork_peak_ratio_ = cork_peak_ratio; }

    //getters
    unsigned GetOvFact () const { return ov_fact_; }
    double GetRrcSpan() const { return rrc_span_; }
    unsigned GetBarkerLength () const { return barker_length_; } 
    double GetRollOff () const { return roll_off_; }
    unsigned GetBarkerZeros () const { return barker_zeros_; }
    unsigned GetDownSamplingFactor() const { return down_sampling_factor_; }
    double GetFTSAmp() const { return fts_amp_; }
    double GetCorkPeakRatio () const { return cork_peak_ratio_; }
    unsigned GetBarkerSampleSize() const { return barker_sample_size_; }
    unsigned GetFTSFFTSize() const { return fts_fft_size_; }
    unsigned GetRRCFFTSize() const { return rrc_fft_size_; }
    unsigned GetPeakBPFFFTSize () const { return peak_bpf_fft_size_; }
    unsigned GetBarkerFFTSize () const { return barker_fft_size_; }
    unsigned GetPeakToDataLength () const { return peak_to_data_length_; }
    unsigned GetRepeatFrequency () const { return repeat_freq_; }
    unsigned GetPeakChecks () const { return peak_checks_; }
    unsigned GetFTSCarrierFrequency() const { return fts_carrier_freq_; }
    double GetPeakThreshold() const { return peak_threshold_; }

    /*
    void DeSerialize (const Value& d); 

    template <typename Writer>
    void Serialize(Writer& writer) const 
    {
    
      writer.StartObject();
    
      writer.Key("ov_fact");
      writer.Uint(ov_fact_);
    
      writer.Key("rrc_span");
      writer.Double(rrc_span_);
    
      writer.Key("barker_length");
      writer.Uint(barker_length_);
    
      writer.Key("roll_off");
      writer.Double(roll_off_);
    
      writer.Key("barker_zeros");
      writer.Uint(barker_zeros_);
    
      writer.Key("down_sampling_factor");
      writer.Uint(down_sampling_factor_);
    
      writer.Key("fts_amplitude");
      writer.Double(fts_amp_);
    
      writer.Key("repeat_frequency");
      writer.Uint(repeat_freq_);
    
      writer.Key("peak_checks");
      writer.Uint(peak_checks_);
    
      writer.Key("fts_carrier_frequency");
      writer.Uint(fts_carrier_freq_);
    
      writer.Key("cork_peak_ratio");
      writer.Double(cork_peak_ratio_);
    
      writer.EndObject();
    }
    */
  private:
    void SetParameters(); 

  private:
    unsigned ov_fact_;
    double rrc_span_;
    unsigned barker_length_;
    double roll_off_;
    unsigned barker_zeros_;
    unsigned down_sampling_factor_;
    double   fts_amp_;
    unsigned barker_sample_size_;
    unsigned fts_fft_size_;
    unsigned rrc_fft_size_;
    unsigned peak_bpf_fft_size_;
    unsigned barker_fft_size_;
    unsigned peak_to_data_length_;
    unsigned repeat_freq_;
    unsigned peak_checks_;
    unsigned fts_carrier_freq_;
    double peak_threshold_;
    double cork_peak_ratio_;


};

// @ class : options 
// @ author: Phani Sai Chand Gali
// @ Date  : Jan 31,2020
// @ brief : Class encapsulating all the parameter settings
class options {
  
  public:
    options() { }; 

    /*
    void DeSerialize (const Value& d); 

    template <typename Writer>
    void Serialize(Writer& writer) const 
    {
       
      writer.StartObject();
   
      writer.Key("CTS");
      CTS.Serialize(writer);
   
      writer.Key("FTS");
      FTS.Serialize(writer);
   
      writer.Key("PayLoad");
      PAYLOAD.Serialize(writer);
   
      writer.EndObject();
    }   
    */
    static CtsParams CTS;
    static FtsParams FTS;
    static PayloadParams PAYLOAD;

};

// @ class : configSettings 
// @ author: Phani Sai Chand Gali
// @ Date  : Jan 31,2020
// @ brief : Start of all the configuration settings (serializing or deserializing)
class ConfigSettings {
  public:
    ConfigSettings(string version_name) : config_version_(version_name),
                                          cts_params_ (options::CTS),
                                          fts_params_ (options::FTS),
                                          payload_params_(options::PAYLOAD)
    { 
      SetupConfig();
    }

  private:
    void SetupConfig();
    /*
    void DeSerialize (const Value& d); 

    template <typename Writer>
    void Serialize(Writer& writer) const
    {
    
      writer.StartObject();
      
      writer.Key(config_version_.c_str());
      opt_.Serialize(writer);
    
      writer.EndObject();
    }
    */
  private:
    string config_version_;

  public:
    const CtsParams& cts_params_;
    const FtsParams& fts_params_;
    const PayloadParams& payload_params_;
   // options opt_;
};

#endif
