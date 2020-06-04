//
// Created by sid on 08/12/19.
//

#ifndef DIRECTORY_TEST_DEMODHELPERS_H
#define DIRECTORY_TEST_DEMODHELPERS_H

#include <core/datastructure/vecWrapper.h>
#include <core/demodulation/config.h>
#include <core/utils/filters/filter.h>
#include <core/all_config.h>

double welchPSD(vector<double> &inputSignal, int nperseg);
//vector<double> welchPSDCB(vector<double> *inputSignal, int nperseg);
vector<double> welchPSDCB(vector<vector<double>> &inputSignal, int nperseg);
vector<double> hanning(int n);
int getIndexForFreq(int freq, int len, int fs);
double getEnergyInBand(vector<double> &inputFFT, int startFreq, int endFreq);
bool checkElementInList(vector<int> &list, int element);

#endif //DIRECTORY_TEST_DEMODHELPERS_H
