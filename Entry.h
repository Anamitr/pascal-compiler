#pragma once

#include "global.h"

using namespace std;

class Entry {
public:
    int indexInSymbolTable;
    int positionInMemory;
    int typeCode;

    string name;
    string typeChar;

    bool isVariable = false;
    bool isFunction = false;
    bool isProcedure = false;

    int memAllocSize = 0;

//    string getName() { return name;}
};
