#pragma once

#include "global.h"

using namespace std;

class Entry {
public:
    int indexInSymbolTable;
    int tokenTypeCode;
    int typeCode;

    int positionInMemory = -1;
    int BPOffset = -9999;

    string name;
    string typeChar;

    bool isVariable = false;
    bool isFunction = false;
    bool isProcedure = false;
    bool isConstant = false;

    int memAllocSize = 0;

    string getPosInMemString();

//    string getName() { return name;}
};
