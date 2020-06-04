#ifndef GLOBAL_VAR_INTERNAL_H
#define GLOBAL_VAR_INTERNAL_H

/* @brief : This file contains all the global variables that are mostly used in demodulation
 *          code. This file is used as an include file for using these variables.
 *          All these variables are defined in all_config.cpp file.
 * @todo :  Need to change the naming of these global variables and remove those that are
 *          not required.
 *          ErrorInfo is not yet used.
 */

typedef void (*DebugInfo) (std::string);
typedef void (*ErrorInfo) (std::string, int);

//-------all the global variables.........
extern std::vector<bool> decodedBits;
//bvec decodedBits;
extern std::vector<double> decodedBitsConfidence;
//vec decodedBitsConfidence;
extern std::vector<int> decodedSymbols;
extern int dataBPFProcessed;
extern bool firstBlock;
extern bool multipleBlocks;
extern bool welCalState;
//bool preambleState = PREAMBLE_STATE;
extern bool preambleState;
extern std::vector<double> audioInputBuffer;
 //temporrary global variable . Needd to be changed
extern std::string decodedDataG;

extern bool ctsEnableState;
extern bool isDataDecoded;

extern int no_of_symbols;
extern int decode_payload_size;

extern int chunkSize;

extern int counterForTime;

extern DATA_TYPE sdkType; //for fec and libtrill
//-----------------------------------------
#endif
