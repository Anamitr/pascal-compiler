#pragma once

#include <ostream>
#include "global.h"

using namespace std;

class Entry {
public:
    int indexInSymbolTable;
    int tokenTypeCode;          // exp. NUM, ID, IF, WHILE
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

    bool isControlStructure = false;
    int controlVariableIndex;
    vector<int> controlLabels;              // for if first label is for false,
                                            // second for exit

    int memAllocSize = 0;
    int numOfPointers = 0;

    vector<int> subprogramArgumentsIndexes;

    string getPosInMemString();
    void assignType(int typeCode);

    friend ostream &operator<<(ostream &os, const Entry &entry);
    string getNameWithTypeString();
    string getNameWithTokenTypeString();

private:
    void shortenIfReal();
};
