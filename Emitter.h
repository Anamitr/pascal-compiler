#pragma once

#include "global.h"
#include "Decoder.h"

using namespace std;

class Emitter {
public:
    void emitString(string stringToEmit);
    void generateOperation(int operationCode, int firstVarIndex, int secondVarIndex);

    void writeToFile(string outputFileName);

private:
    string output;
};
