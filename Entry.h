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

    string name;        // name may be subprogram, variable name or literal value
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

    vector<int> subprogramArgumentsIndexes;

    string getPosInMemString();
    void assignType(int typeCode);

    friend ostream &operator<<(ostream &os, const Entry &entry);
    string getNameWithTypeString();
};
