#pragma once

#include "global.h"
#include "Entry.h"

using namespace std;

class SymbolTable {
public:
    int lookup(const string);
    int insert(const string name, int typeOfToken);

    void addGlobalVariablesWithType(list<int> idList, int type);

private:
    vector<Entry> entries;
    int freeMemoryPointer = 0;
};

