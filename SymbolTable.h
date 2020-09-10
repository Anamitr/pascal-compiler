#pragma once

#include "global.h"
//#include "Entry.h"

using namespace std;

class Entry;

class SymbolTable {
public:
    int lookup(const string);
    int insert(const string name, int typeOfToken, int typeCode);

    Entry& getEntryByIndex(int index);
    Entry allocateTempVarOfType(int typeCode);
//    string getEntryNameByIndex(int index);
    Entry allocateFunReturnVarPointer(Entry& functionEntry);

    void addGlobalVariablesWithType(list<int> indexList, int typeCode);
    void assignVariableItsType(Entry& entry, int typeCode);

    int currentlyProcessedSubprogramIndex = -1;

private:
    vector<Entry> entries;
    int freeMemoryPointer = 0;
    int tempVarCounter = 0;
    int BPOffsetPointer = 8;
};

