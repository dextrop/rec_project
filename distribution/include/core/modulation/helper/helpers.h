#ifndef MODULATION_HELPERS_H
#define MODULATION_HELPERS_H

/* @brief : This file consists of all the helper functions related to modulation
 */

#include <vector>
#include <core/datastructure/vecWrapper.h>
#include <core/utils/common_helper/helper.h>
#include <core/all_config.h>


std::vector<double> GenerateSymbol(int freq1, int freq2, int gaurd_band_size = (options::PAYLOAD).GetGuardBandZeros(), int symbol_block_size = (options::PAYLOAD).GetSymbolDataSize(), int flat_region_size = (options::PAYLOAD).GetFlatRegionSize());

void GenerateSymbol(std::vector<double>& output_signal, int freq1, int freq2, int gaurd_band_size = (options::PAYLOAD).GetGuardBandZeros(), int symbol_block_size = (options::PAYLOAD).GetSymbolDataSize(), int flat_region_size = (options::PAYLOAD).GetFlatRegionSize());

void GenerateEyeShapeFilter (int flat_region_size, int filter_size, double amp,std::vector<double>& eye_filter);
std::vector<double> GenerateEyeShapeFilter (int flat_region_size, int filter_size, double amp);


void GenerateSineTone(int freq, int size, std::vector<double>& signal_output);
std::vector<double> GenerateSineTone(int freq, int size);

vector<double> UpSampleData (const vector<double>& data, int up_sampling_factor);

#endif //DIRECTORY_TEST_HELPERS_H
