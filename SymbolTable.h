#pragma once

#include "global.h"
#include "Entry.h"

using namespace std;

class SymbolTable {
public:
    int lookup(const string);
    int insert(const string name, int typeOfToken);

    Entry getEntryByIndex(int index);
    Entry allocateTempVarOfType(int typeCode);

    void addGlobalVariablesWithType(list<int> idList, int typeCode);

private:
    vector<Entry> entries;
    int freeMemoryPointer = 0;
    int tempVarCounter = 0;
};

