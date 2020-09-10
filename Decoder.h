#pragma once

#include "global.h"

using namespace std;

class Decoder {
public:
    static string decodeSign(int signCode);
    static int getVarTypeSize(int typeCode);
    static string getShortTypeSignFromCode(int typeCode);
//    static string getLongTypeStringFromCode(int typeCode);
    static string getConversionStringFromCode(int conversionCode);
    static int getConversionResultType(int conversionCode);
    static int getConversionCodeFromEntriesTypes(int oldType, int newType);
    static string getTokenTypeStringFromCode(int tokenTypeCode);
};

