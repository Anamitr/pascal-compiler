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

int Emitter::generateSignOperation(int operationCode, Entry leftEntry, Entry rightEntry) {
    string command = "\t";
    string operation = Decoder::decodeSign(operationCode);
    cout << "Emitter::generateSignOperation\t\t\t" << "Got operation: " << operation << endl;
    command.append(operation + ".");

    int operationVarType = UNKOWN;

    if (leftEntry.typeCode != rightEntry.typeCode) {
        vector<Entry> convertedEntries = this->convertToSameType(leftEntry, rightEntry);
        leftEntry = convertedEntries[0];
        rightEntry = convertedEntries[1];
    }

    if (leftEntry.typeCode == rightEntry.typeCode) {
        operationVarType = leftEntry.typeCode;
        command.append(Decoder::getShortTypeSignFromCode(operationVarType) + "\t");
        command.append(to_string(leftEntry.positionInMemory) + ",");
        command.append(to_string(rightEntry.positionInMemory) + ",");
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
                Decoder::getConversionCodeFromEntriesTypes(rightEntry.typeCode,
                                                           leftEntry.typeCode), rightEntry);
        entryToAssign = convertedRightEntry;
    }
    cout << "Emitter::generateAssignOperation\t\t" << "assign vars: " << leftEntry.name << " := " << entryToAssign.name << endl;
    string assignValue = entryToAssign.isConstant ? "#" + entryToAssign.name :
                         entryToAssign.getPosInMemString();
    string command = "\t";
    command.append("mov." + leftEntry.typeChar + "\t");
    command.append(assignValue + ",");
    command.append(leftEntry.getPosInMemString());
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

vector<Entry> Emitter::convertToSameType(Entry leftEntry, Entry rightEntry) {
    vector<Entry> result;
    if (leftEntry.typeCode == rightEntry.typeCode) {
        cout << "Emitter::convertToSameType\t\t\t" << "entries are the same type!";
    } else if (leftEntry.typeCode == INTEGER && rightEntry.typeCode == REAL) {
        int conversionCode = INT_TO_REAL;
        leftEntry = generateConversion(conversionCode, leftEntry);
    } else if (leftEntry.typeCode == REAL && rightEntry.typeCode == INTEGER) {
        int conversionCode = INT_TO_REAL;
        rightEntry = generateConversion(conversionCode, rightEntry);
    }
    result.push_back(leftEntry);
    result.push_back(rightEntry);
    return result;
}

// "$" + subprogramEntry.name + "allocSize"     - will be put subprogram alloc size later
void Emitter::emitSubprogramStart(Entry subprogramEntry) {
    if (subprogramEntry.isProcedure == false && subprogramEntry.isFunction == false) {
        cout << "Emitter::emitSubprogramStart\t\t\t" << "entry is neither procedure nor a function!";
        exit(-1);
    } else {
        string command = subprogramEntry.name + ":\n";
        command.append("\tenter.i\t#$" + subprogramEntry.name + "allocSize");
        this->emitString(command);
    }
    if (subprogramEntry.isFunction) {
        symbolTable.allocateFunReturnVarPointer(subprogramEntry);
    }
}

void Emitter::emitSubprogramLeave() {
    setSubprogramMemAllocSize();
    string command = "\tleave\n\treturn";
    this->emitString(command);
}

void Emitter::setSubprogramMemAllocSize() {
//    output.replace("$" + subprogramEntry.name + "allocSize", to_string(memAllocSize));
    Entry subprogramEntry = symbolTable.getEntryByIndex(
            symbolTable.currentlyProcessedSubprogramIndex);
    string subProgramMemAllocSizeVar = "$" + subprogramEntry.name + "allocSize";
    replaceInString(output, subProgramMemAllocSizeVar,
                    to_string(subprogramEntry.memAllocSize));
}

int Emitter::callSubprogram(const Entry &subprogramEntry) {
    cout << "Emitter::callSubprogram\t\t\t\t" << "calling subprogram " << subprogramEntry.name << endl;
    int result = -1;
    int subprogramStackPointer = 0;
    if (subprogramEntry.isFunction) {
        Entry funReturnVar = symbolTable.allocateTempVarOfType(subprogramEntry.typeCode);
        this->emitString("\tpush.i  #" + funReturnVar.getPosInMemString());
        subprogramStackPointer++;
        result = funReturnVar.indexInSymbolTable;
    }
    this->emitString("\tcall.i\t#" + subprogramEntry.name);
    if (subprogramStackPointer != 0) {
        this->emitString("\tincsp.i\t#" + to_string(subprogramStackPointer *
                                                    Decoder::getVarTypeSize(INTEGER)));
    }
    cout << "Emitter::callSubprogram\t\t\t\t" << "result = " << result << endl;
    return result;
}

//Entry Emitter::generateMulOperation(Entry leftEntry, Entry rightEntry) {
//    return Entry();
//}
