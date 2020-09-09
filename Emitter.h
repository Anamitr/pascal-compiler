#pragma once

#include "global.h"
#include "Decoder.h"
#include "Entry.h"

using namespace std;

class Emitter {
public:
    void emitString(string stringToEmit);
    int generateSignOperation(int operationCode, int firstVarIndex, int secondVarIndex);
    int generateAssignOperation(Entry leftEntry, Entry rightEntry);
    Entry generateConversion(int conversionCode, Entry varToConvert);

    void writeToFile(string outputFileName);

private:
    string output;
};
