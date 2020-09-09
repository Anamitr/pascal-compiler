#include "Emitter.h"


Emitter emitter = Emitter();

void Emitter::emitString(string stringToEmit) {
    output.append(stringToEmit + "\n");
}

void Emitter::writeToFile(string outputFileName) {
    ofstream outputStream(outputFileName);
    outputStream << output;
    outputStream.close();
}

int Emitter::generateSignOperation(int operationCode, int firstVarIndex, int secondVarIndex) {
    string command = "\t";
    string operation = Decoder::decodeSign(operationCode);
    cout << "Got operation: " << operation << endl;
    command.append(operation + ".");

    Entry firstVar = symbolTable.getEntryByIndex(firstVarIndex);
    Entry secondVar = symbolTable.getEntryByIndex(secondVarIndex);
    int operationVarType = UNKOWN;
    if (firstVar.typeCode == secondVar.typeCode) {
        operationVarType = firstVar.typeCode;
        command.append(Decoder::getShortTypeSignFromCode(operationVarType) + "\t");
        command.append(to_string(firstVar.positionInMemory) + ",");
        command.append(to_string(secondVar.positionInMemory) + ",");
        Entry resultEntry = symbolTable.allocateTempVarOfType(operationVarType);
        command.append(to_string(resultEntry.positionInMemory));
        this->emitString(command);
        return resultEntry.indexInSymbolTable;
    } else {
        // TODO: typeCode conversion
        cout << "Type conversion not implemented" << endl;
    }

}

int Emitter::generateAssignOperation(Entry leftEntry, Entry rightEntry) {

    Entry entryToAssign = rightEntry;

    if (leftEntry.typeCode != rightEntry.typeCode) {
        Entry convertedRightEntry = generateConversion(
                Decoder::getConversionCodeFromEntriesTypes(rightEntry.typeCode, leftEntry.typeCode),
                rightEntry);
        entryToAssign = convertedRightEntry;
    }
    cout << "Assign vars: " << leftEntry.name << " := " << entryToAssign.name << endl;
    string command = "\t";
    command.append("mov." + leftEntry.typeChar + "\t");
    command.append(to_string(entryToAssign.positionInMemory) + ",");
    command.append(to_string(leftEntry.positionInMemory));
    this->emitString(command);
}

Entry Emitter::generateConversion(int conversionCode, Entry varToConvert) {
    string command = "\t";
    command.append(Decoder::getConversionStringFromCode(conversionCode) + ".");
    command.append(Decoder::getShortTypeSignFromCode(varToConvert.typeCode) + "\t");
    command.append(to_string(varToConvert.positionInMemory) + ",");
    Entry resultEntry = symbolTable.allocateTempVarOfType(
            Decoder::getConversionResultType(conversionCode));
    command.append(to_string(resultEntry.positionInMemory));
    this->emitString(command);
    return resultEntry;
}

void Emitter::emitWrite(Entry varToWrite) {
    string command = "\t";
    command.append("write." + varToWrite.typeChar + "\t" + to_string(varToWrite.positionInMemory));
    this->emitString(command);
}
