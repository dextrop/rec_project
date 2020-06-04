#ifndef MODULATION_HEADER_H
#define MODULATION_HEADER_H 

/* @ brief : This file consists of all the functionalities related to modulation header 
 * @ todo  : Barker vector is fixed ??
 */


#include <core/utils/filters/filter.h>
#include <core/modulation/helper/helpers.h>
#include <core/all_config.h>


// @ class : ModulationHeader 
// @ author: Phani Sai Chand Gali
// @ Date  : Apr 1,2020
// @ brief : Class responsible for all the modulation header functionalities
class ModulationHeader {

public:
  ModulationHeader();
  void GenerateHeader(std::vector<double>& header_signal);
  std::vector<double> GenerateHeader();
  void SetCallBack (DebugInfo callback_fun);
  
private:
  void GenerateFts(std::vector<double>& fts_signal);
  void GenerateCts(std::vector<double>& cts_signal);

private:
  std::vector<double> barker_;
  const CtsParams& cts_params_;
  const FtsParams& fts_params_;
  DebugInfo debug_info_;
};

#endif
