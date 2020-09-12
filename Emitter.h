#pragma once

#include "global.h"
#include "Decoder.h"

using namespace std;

class Entry;

class Emitter {
public:
    // Plain emit
    void emitString(string stringToEmit);

    // Type conversion
    Entry generateConversion(int conversionCode, Entry varToConvert);
    vector<Entry> convertToSameType(Entry leftEntry, Entry rightEntry);

    // Input-output built-in functions
    void emitWrite(list<int> callArguments);
    void emitRead(list<int> callArguments);

    // Double sided operators
    int generateSignOperation(int operationCode, Entry leftEntry, Entry rightEntry);
    int generateAssignOperation(Entry leftEntry, Entry rightEntry);
    int generateRelop(int relopCode, Entry& leftEntry, Entry& rightEntry);

    // Label
    void generateJump(int labelNumber);
    void generateLabel(int labelNumber);

    // Subprogram
    void emitSubprogramStart(Entry& subprogramEntry);
    void emitSubprogramLeave();
    void setSubprogramMemAllocSize();
    int callSubprogram(Entry& subprogramEntry, const list<int>& callArguments);
    int callSubprogram(Entry& subprogramEntry);

    // IF structure generation
    void generateIfHeader(Entry& ifStructureEntry);
    void generateThenJump(int ifStructureIndex);
    void generateElseLabel(int ifStructureIndex);
    void generateExitLabel(int ifStructureIndex);

    // WHILE structure generation
    void generateWhileHeader(Entry& whileStructureEntry);
    void generateWhileCheckJump(Entry& whileStructureEntry);
    void generateWhileEnd(Entry& whileStructureEntry);

    // NOT
    int generateNOTOperation(Entry& entryToBeNegated);

    // Assign pointer addresses after subprogram declarations
    void writePointerAddresses();

    // Write final output
    void writeToFile(string outputFileName);

private:
    string output;
};
