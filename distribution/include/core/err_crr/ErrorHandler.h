//
// Created by sid on 13/12/19.
//

#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <string.h>

using namespace std;

namespace trill {

class ErrorHandler {
public:
    ErrorHandler();
    string filetag;
    void size_check(int obtained_size, int org_size, string fn_tag);
};


} //namespace trill
#endif //DIRECTORY_TEST_ERROR_H
