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
    Entry allocateFunReturnVarPointer(Entry& functionEntry);
    void pushParametersToStack(list<int> indexList, int typeCode);

    void addGlobalVariablesWithType(list<int> indexList, int typeCode);
    void addLocalVariableWithType(int index, int typeCode);
    list<Entry> assignPointerAddresses();
    void assignSubprogramItsArguments(Entry& subprogramEntry, list<int>& argumentsIndexes);
    void addLocalDeclaredVariablesWithType(list<int> indexList, int typeCode);
    int addControlStructure(int controlStructureType, int controlVariableIndex = -1);

    int currentlyProcessedSubprogramIndex = -1;
    int labelCounter = 1;
    vector<int> controlStructureStack;

private:
    vector<Entry> entries;
    list<int> parametersStack;
    int freeMemoryPointer = 0;
    int BPUpperOffsetPointer = 8;
    int BPLowerOffsetPointer = 0;
    int tempVarCounter = 0;
    int controlStructureCounter = 0;

};

