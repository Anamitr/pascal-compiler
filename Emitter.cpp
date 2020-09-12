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
    cout << "Emitter::generateSignOperation\t\t\t" << "Got operation: " << operation
         << " between " << leftEntry.name << "(" << leftEntry.typeChar << ") and "
         << rightEntry.name << "(" << rightEntry.typeChar << ")" << endl;
    command.append(operation + ".");

    int operationVarType = UNKOWN;

    if (leftEntry.typeCode != rightEntry.typeCode) {
        vector<Entry> convertedEntries = this->convertToSameType(leftEntry, rightEntry);
        leftEntry = convertedEntries[0];
        rightEntry = convertedEntries[1];
    }

    operationVarType = leftEntry.typeCode;
    command.append(Decoder::getShortTypeSignFromCode(operationVarType) + "\t");
    command.append(leftEntry.getPosInMemString() + ",");
    command.append(rightEntry.getPosInMemString() + ",");
    Entry resultEntry = symbolTable.allocateTempVarOfType(operationVarType);
    command.append(resultEntry.getPosInMemString());
    this->emitString(command);
    return resultEntry.indexInSymbolTable;

}

int Emitter::generateAssignOperation(Entry leftEntry, Entry rightEntry) {
    Entry entryToAssign = rightEntry;
    cout << "Emitter::generateAssignOperation\t\t" << "assign vars: "
         << leftEntry.getNameWithTypeString() << " := " << entryToAssign.name << endl;

    if (leftEntry.typeCode != rightEntry.typeCode) {
        cout << "Emitter::generateAssignOperation\t\t" << "need to convert "
             << rightEntry.getNameWithTypeString() << " to " << leftEntry.typeChar << endl;
        Entry convertedRightEntry = generateConversion(
                Decoder::getConversionCodeFromEntriesTypes(rightEntry.typeCode,
                                                           leftEntry.typeCode), rightEntry);
        entryToAssign = convertedRightEntry;
    }

    string assignValue = entryToAssign.isConstant ? "#" + entryToAssign.name :
                         entryToAssign.getPosInMemString();
    string command = "\t";
    command.append("mov." + leftEntry.typeChar + "\t");
    command.append(assignValue + ",");
    command.append(leftEntry.getPosInMemString());
    this->emitString(command);
}

Entry Emitter::generateConversion(int conversionCode, Entry varToConvert) {
    string conversionString = Decoder::getConversionStringFromCode(conversionCode);
    cout << "Emitter::generateConversion\t\t\t" << "Converting " << varToConvert.name
         << "(" << varToConvert.typeChar << ") " << conversionString << endl;
    string command = "\t";
    command.append(conversionString + ".");
    command.append(Decoder::getShortTypeSignFromCode(varToConvert.typeCode) + "\t");
    command.append(varToConvert.getPosInMemString() + ",");
    Entry resultEntry = symbolTable.allocateTempVarOfType(
            Decoder::getConversionResultType(conversionCode));
    command.append(resultEntry.getPosInMemString());
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
void Emitter::emitSubprogramStart(Entry &subprogramEntry) {
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
        cout << "Emitter::emitSubprogramStart\t\t\t" << "dupa " << subprogramEntry.BPOffset << endl;
    }
}

void Emitter::emitSubprogramLeave() {
    setSubprogramMemAllocSize();
    string command = "\tleave\n\treturn";
    this->emitString(command);
}

void Emitter::setSubprogramMemAllocSize() {
    Entry subprogramEntry = symbolTable.getEntryByIndex(
            symbolTable.currentlyProcessedSubprogramIndex);
    subprogramEntry.memAllocSize = localMemAllocSize;
    localMemAllocSize = 0;
    string subProgramMemAllocSizeVar = "$" + subprogramEntry.name + "allocSize";
    replaceInString(output, subProgramMemAllocSizeVar,
                    to_string(subprogramEntry.memAllocSize));
}

int Emitter::callSubprogram(Entry &subprogramEntry, const list<int> &callArguments) {
    vector<int> callArgumentsVector{std::begin(callArguments), std::end(callArguments)};
    cout << "Emitter::callSubprogram\t\t\t\t" << "calling subprogram " << subprogramEntry.name
         << " with arguments (" << callArgumentsVector.size() << "):" << endl;

    for (int i = 0; i < callArgumentsVector.size(); i++) {
        Entry argEntry = symbolTable.getEntryByIndex(callArgumentsVector.at(i));
        int addrToPush = -9999;

        Entry correspondingPointerEntry = symbolTable.getEntryByIndex(subprogramEntry
                                                                              .subprogramArgumentsIndexes.at(i));
        if (argEntry.typeCode != correspondingPointerEntry.typeCode) {
            cout << "Emitter::callSubprogram\t\t\t\t" << "Argument type doesn't match, got "
                 << argEntry.typeChar << ", expected " << correspondingPointerEntry.typeChar << endl;
            argEntry = this->generateConversion(Decoder::getConversionCodeFromEntriesTypes(
                    argEntry.typeCode, correspondingPointerEntry.typeCode), argEntry);
        }

        if (argEntry.isConstant) {
            Entry tempVar = symbolTable.allocateTempVarOfType(argEntry.typeCode);
            this->generateAssignOperation(tempVar, argEntry);
            addrToPush = tempVar.positionInMemory;
        } else {
            addrToPush = argEntry.positionInMemory;
        }
        this->emitString("\tpush.i\t#" + to_string(addrToPush));
        subprogramEntry.numOfPointers += 1;
    }
    cout << endl;

    int result = callSubprogram(subprogramEntry);
    return result;
}

int Emitter::callSubprogram(Entry &subprogramEntry) {
    cout << "Emitter::callSubprogram\t\t\t\t" << "calling subprogram " << subprogramEntry.name << endl;
    int result = -1;
    if (subprogramEntry.isFunction) {
        Entry funReturnVar = symbolTable.allocateTempVarOfType(subprogramEntry.typeCode);
        this->emitString("\tpush.i  #" + funReturnVar.getPosInMemString());
        subprogramEntry.numOfPointers += 1;
        result = funReturnVar.indexInSymbolTable;
    }
    this->emitString("\tcall.i\t#" + subprogramEntry.name);
    if (subprogramEntry.numOfPointers != 0) {
        this->emitString("\tincsp.i\t#" + to_string(subprogramEntry.numOfPointers *
                                                    Decoder::getVarTypeSize(INTEGER)));
    }
    cout << "Emitter::callSubprogram\t\t\t\t" << "result = " << result << endl;
    return result;
}

void Emitter::writePointerAddresses() {
    list<Entry> pointerEntries = symbolTable.assignPointerAddresses();
    for (Entry pointerEntry : pointerEntries) {
        cout << "Emitter::writePointerAddresses\t\t\t" << pointerEntry.name
             << " - " << pointerEntry.posInMemoryString << endl;
        replaceInString(output, "${" + pointerEntry.name + "-memAddr}",
                        pointerEntry.posInMemoryString);
    }
}

// returns entry index where operation result is stored
int Emitter::generateRelop(int relopCode, Entry &leftEntry, Entry &rightEntry) {
    string relopCommand = Decoder::getRelopCommandStringFromCode(relopCode);
    cout << "Emitter::generateRelop\t\t\t\t" << "Got operation: " << relopCommand
         << " between " << leftEntry.name << "(" << leftEntry.typeChar << ") and "
         << rightEntry.name << "(" << rightEntry.typeChar << ")" << endl;
    //TODO: What type relop command should be?
    string command = "\t" + relopCommand + "." + leftEntry.typeChar + "\t";
    command += leftEntry.getPosInMemString() + "," + rightEntry.getPosInMemString() + ",";
    int firstLabelNum = symbolTable.labelCounter++;
    command += "#lab" + to_string(firstLabelNum);
    Entry resultEntry = symbolTable.allocateTempVarOfType(INTEGER);
//    Entry stubZeroEntry = getStubLiteralEntry("0");
    this->emitString(command);
    generateAssignOperation(resultEntry, getStubLiteralEntry("0", INTEGER));
    int secondLabelNum = symbolTable.labelCounter++;
    this->generateJump(secondLabelNum);
    this->generateLabel(firstLabelNum);
    this->generateAssignOperation(resultEntry, getStubLiteralEntry("1", INTEGER));
    this->generateLabel(secondLabelNum);
    return resultEntry.indexInSymbolTable;
}

void Emitter::generateJump(int labelNumber) {
    this->emitString("\tjump.i\t#lab" + to_string(labelNumber));
}

void Emitter::generateLabel(int labelNumber) {
    this->emitString("lab" + to_string(labelNumber) + ":");
}

void Emitter::generateIfHeader(Entry &ifEntry) {
    Entry controlVariableEntry = symbolTable.getEntryByIndex(ifEntry.controlVariableIndex);
    int falseLabelNum = symbolTable.labelCounter++;
    ifEntry.controlLabels.push_back(falseLabelNum);
    string command = "\tje.i\t" + controlVariableEntry.getPosInMemString() + ",#0,#lab";
    command += to_string(falseLabelNum);
    this->emitString(command);
}

void Emitter::generateThenJump(int ifStructureIndex) {
    Entry &ifStructureEntry = symbolTable.getEntryByIndex(ifStructureIndex);
    cout << "Emitter::generateThenJump\t\t\t" << ifStructureEntry.getNameWithTokenTypeString()
         << "" << endl;
    int exitLabelNum = symbolTable.labelCounter++;
    ifStructureEntry.controlLabels.push_back(exitLabelNum);
    string command = "\tjump.i\t#lab" + to_string(exitLabelNum);
    this->emitString(command);
}

void Emitter::generateElseLabel(int ifStructureIndex) {
    Entry &ifStructureEntry = symbolTable.getEntryByIndex(ifStructureIndex);
    cout << "Emitter::generateElseLabel\t\t\t" << ifStructureEntry.getNameWithTokenTypeString()
         << "" << endl;
    this->generateLabel(ifStructureEntry.controlLabels.at(0));
}

void Emitter::generateExitLabel(int ifStructureIndex) {
    Entry &ifStructureEntry = symbolTable.getEntryByIndex(ifStructureIndex);
    cout << "Emitter::generateExitLabel\t\t\t" << ifStructureEntry.getNameWithTokenTypeString()
         << "" << endl;
    this->generateLabel(ifStructureEntry.controlLabels.at(1));
    symbolTable.controlStructureStack.pop_back();
}

void Emitter::generateWhileHeader(Entry &whileStructureEntry) {
    cout << "Emitter::generateWhileHeader\t\t\t" << whileStructureEntry.name << endl;
    int exitWhileLabel = symbolTable.labelCounter++;
    whileStructureEntry.controlLabels.push_back(exitWhileLabel);
    int beginningWhileLabel = symbolTable.labelCounter++;
    whileStructureEntry.controlLabels.push_back(beginningWhileLabel);
    this->generateLabel(beginningWhileLabel);
}

void Emitter::generateWhileCheckJump(Entry &whileStructureEntry) {
    cout << "Emitter::generateWhileCheckJump\t\t\t" << whileStructureEntry.name << endl;
    Entry controlVariableEntry = symbolTable
            .getEntryByIndex(whileStructureEntry.controlVariableIndex);
    string command = "\tje.i\t" + controlVariableEntry.getPosInMemString()
                     + ",#0,#lab" + to_string(whileStructureEntry.controlLabels.at(0));
    this->emitString(command);
}

void Emitter::generateWhileEnd(Entry &whileStructureEntry) {
    cout << "Emitter::generateWhileEnd\t\t\t" << whileStructureEntry.name << endl;
    this->generateJump(whileStructureEntry.controlLabels.at(1));
    this->generateLabel(whileStructureEntry.controlLabels.at(0));
}

int Emitter::generateNOTOperation(Entry &entryToBeNegated) {
    cout << "Emitter::generateNOTOperation\t\t\t" << entryToBeNegated.name << endl;
    int firstLabel = symbolTable.labelCounter++;
    int secondLabel = symbolTable.labelCounter++;
    Entry resultEntryIndex = symbolTable.allocateTempVarOfType(INTEGER);

    string isEqualCommand = "\tje.i\t" + entryToBeNegated.getPosInMemString()
            + ",#0,#lab" + to_string(firstLabel);
    this->emitString(isEqualCommand);
    string returnZeroCommand = "\tmov.i\t#0," + resultEntryIndex.getPosInMemString();
    this->emitString(returnZeroCommand);
    this->generateJump(secondLabel);
    this->generateLabel(firstLabel);
    string returnOneCommand = "\tmov.i\t#1," + resultEntryIndex.getPosInMemString();
    this->emitString(returnOneCommand);
    this->generateLabel(secondLabel);

    return resultEntryIndex.indexInSymbolTable;
}

