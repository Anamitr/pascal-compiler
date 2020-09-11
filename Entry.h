#pragma once

#include <ostream>
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
    string posInMemoryString;

    bool isVariable = false;
    bool isFunction = false;
    bool isProcedure = false;
    bool isConstant = false;
    bool isPointer = false;
    bool isLocal = false;

    int memAllocSize = 0;
    int numOfPointers = 0;

    string getPosInMemString();
    void assignType(int typeCode);

//    string getName() { return name;}
    friend ostream &operator<<(ostream &os, const Entry &entry);
};
