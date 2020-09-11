#pragma once

#include "global.h"
#include "Decoder.h"
//#include "Entry.h"

using namespace std;

class Entry;

class Emitter {
public:
    void emitString(string stringToEmit);
    int generateSignOperation(int operationCode, Entry leftEntry, Entry rightEntry);
    int generateAssignOperation(Entry leftEntry, Entry rightEntry);
    Entry generateConversion(int conversionCode, Entry varToConvert);
    vector<Entry> convertToSameType(Entry leftEntry, Entry rightEntry);

    void emitWrite(Entry varToWrite);
    void emitSubprogramStart(Entry& subprogramEntry);
    void emitSubprogramLeave();
    void setSubprogramMemAllocSize();
    int callSubprogram(Entry& subprogramEntry, const list<int>& callArguments);
    int callSubprogram(Entry& subprogramEntry);

    void writePointerAddresses();
    void writeToFile(string outputFileName);

private:
    string output;
};
