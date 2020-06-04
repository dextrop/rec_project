//
// Created by sid on 07/12/19.
//

#ifndef GOLBALVAR_H
#define GOLBALVAR_H

#include <core/datastructure/vecWrapper.h>

extern vector<double> audioInputBuffer;
extern bool preambleState;
extern bool firstBlock;
extern bool welCalState;
extern int dataBPFProcessed;
extern bool ctsEnableState;
extern bvec originalBits;
extern bool isDataDecoded;
extern int no_of_symbols;
extern int data_size_full;
#endif //DIRECTORY_TEST_GOLBALVAR_H
