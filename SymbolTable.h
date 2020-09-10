#pragma once

#include "global.h"
#include "Entry.h"

using namespace std;

class SymbolTable {
public:
    int lookup(const string);
    int insert(const string name, int typeOfToken);

    Entry& getEntryByIndex(int index);
    Entry allocateTempVarOfType(int typeCode);
//    string getEntryNameByIndex(int index);

    void addGlobalVariablesWithType(list<int> idList, int typeCode);

    int currentlyProcessedSubprogramIndex = -1;

private:
    vector<Entry> entries;
    int freeMemoryPointer = 0;
    int tempVarCounter = 0;
};

