//
// Created by sid on 13/12/19.
//

#ifndef TRILLVAR_H
#define TRILLVAR_H

enum class CODES
{
    SDK_SETUP_OK = 200,
    MAX_PAYLOAD_EXCEEDED = 501,
    INVALID_SDK = 502,
};

enum class DATA_TYPE
{
    ALPHANUMERIC = 10,
    CHAR = 11,
    DIGIT = 12,
    C2D2 = 13,
    CHAR10 = 14,
    DIGIT10 = 15,
    OTP4 = 16,
    LIQUIDCHAR10 = 17,
};

enum class SYMBOLS_COUNT{
    SMALL = 78,
    BIG = 155,
};

#endif //TRILLVAR_H
