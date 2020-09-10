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

//    string getName() { return name;}
};
