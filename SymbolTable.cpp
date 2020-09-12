#include "SymbolTable.h"

SymbolTable symbolTable = SymbolTable();

int SymbolTable::lookup(const string name) {
//    cout << "lookup entries.size: " << entries.size() << endl;
    for (int i = 0; i < entries.size(); i++) {
//        cout << "names: " << entries[i].name << " , " << name << endl;
        if (entries[i].name == name) {
            return i;
        }
    }
    return -1;
}

int SymbolTable::insert(const string name, int typeOfToken, int typeCode) {
    Entry entry = Entry();
    entry.tokenTypeCode = typeOfToken;
    if (typeOfToken == NUM) entry.isConstant = true;
    entry.name = name;
    if (typeCode != -1) entry.assignType(typeCode);

    int p = entries.size();
    entry.indexInSymbolTable = p;
    entries.push_back(entry);
    cout << "SymbolTable::insert\t\t\t\t" << "Added entry with name " << name << " and tokenTypeCode " <<
         Decoder::getTokenTypeStringFromCode(typeOfToken) << " at index " << p << endl;
    return p;
}

void SymbolTable::addGlobalVariablesWithType(list<int> indexList, int typeCode) {
    string idsMsg = "";
    idsMsg.append("SymbolTable::addGlobalVariablesWithType\t\tindexList: ");
    for (int index : indexList) {
        idsMsg.append(to_string(index) + ", ");
        entries.at(index).assignType(typeCode);
        entries[index].positionInMemory = freeMemoryPointer;
        cout << "SymbolTable::addGlobalVariablesWithType\t\tVariable "
             << entries[index].name << " allocated at " << freeMemoryPointer << endl;
        freeMemoryPointer += Decoder::getVarTypeSize(typeCode);
    }
    idsMsg.append("\n");
    cout << idsMsg;
}

Entry &SymbolTable::getEntryByIndex(int index) {
    cout << "SymbolTable::getEntryByIndex\t\t\t" << index << endl;
    return entries.at(index);
}

Entry SymbolTable::allocateTempVarOfType(int typeCode) {
    int p = this->insert("t" + to_string(tempVarCounter++), ID, typeCode);
    Entry &entry = this->getEntryByIndex(p);
    if (isGlobal) {
        list<int> ids;
        ids.push_back(p);
        addGlobalVariablesWithType(ids, typeCode);
    } else {
        entry.typeCode = typeCode;
        entry.isLocal = true;
        int entrySize = Decoder::getVarTypeSize(typeCode);
        localMemAllocSize += entrySize;
        this->BPLowerOffsetPointer -= entrySize;
        entry.BPOffset = this->BPLowerOffsetPointer;
        cout << "SymbolTable::allocateTempVarOfType\t\t" << "Allocated local temp var name: "
             << entry.name << ", pos in memory: " << entry.getPosInMemString() << endl;
    }
    return entry;
}

Entry SymbolTable::allocateFunReturnVarPointer(Entry &functionEntry) {
    functionEntry.BPOffset = BPUpperOffsetPointer;
    BPUpperOffsetPointer += Decoder::getVarTypeSize(INTEGER);
    cout << "SymbolTable::allocateFunReturnVarPointer\t" + functionEntry.name +
            "(" + functionEntry.typeChar << ")[" << functionEntry.indexInSymbolTable
         << "], BPOffset = " << functionEntry.BPOffset << endl;
    return functionEntry;
}

void SymbolTable::pushParametersToStack(list<int> indexList, int typeCode) {
    for (int index : indexList) {
        parametersStack.push_front(index);
        Entry &entry = symbolTable.getEntryByIndex(index);
        entry.isPointer = true;
        entry.assignType(typeCode);
        cout << "SymbolTable::pushParametersToStack\t\t" << "Pushed parameter " << entry.name
             << "(" << entry.typeChar << ")" << endl;
    }
}

list<Entry> SymbolTable::assignPointerAddresses() {
    list<Entry> result;
    for (int index : this->parametersStack) {
        Entry entry = this->getEntryByIndex(index);
        entry.BPOffset = this->BPUpperOffsetPointer;
        BPUpperOffsetPointer += Decoder::getVarTypeSize(INTEGER);
        entry.posInMemoryString = "*BP+" + to_string(entry.BPOffset);
        result.push_back(entry);
        cout << "SymbolTable::assignPointerAddresses\t\t" << entry.name << ", " <<
             entry.posInMemoryString << endl;
    }
    return result;
}

void SymbolTable::assignSubprogramItsArguments(Entry &subprogramEntry, list<int> &argumentsIndexes) {
    subprogramEntry.subprogramArgumentsIndexes = {std::begin(argumentsIndexes),
                                                  std::end(argumentsIndexes)};
    cout << "SymbolTable::assignSubprogramItsArguments\t" << subprogramEntry.name << ": ";
    for (int i : subprogramEntry.subprogramArgumentsIndexes) {
        Entry argument = this->getEntryByIndex(i);
        cout << argument.name << ", ";
    }
    cout << endl;
}

void SymbolTable::addLocalDeclaredVariablesWithType(list<int> indexList, int typeCode) {
    int entrySize = Decoder::getVarTypeSize(typeCode);
    for (int index : indexList) {
        Entry& localVar = this->getEntryByIndex(index);
        localVar.assignType(typeCode);
//        this->assignVariableItsType(localVar, typeCode);
        localVar.isLocal = true;
        localMemAllocSize += entrySize;
        this->BPLowerOffsetPointer -= entrySize;
        localVar.BPOffset = this->BPLowerOffsetPointer;
        cout << "SymbolTable::addLocalDeclaredVariablesWithType\t"
             << "Allocated local persistent var, name: " << localVar.name << "("
             << localVar.typeChar <<"), pos in memory: "
             << localVar.getPosInMemString() << endl;
    }
}

int SymbolTable::addControlStructure(int controlStructureType, int controlVariableIndex) {
    cout << "SymbolTable::addControlStructure\t\t\t" << endl;
    int entryIndex = this->insert("cs" + to_string(this->controlStructureCounter),
                                  controlStructureType, -1);
    Entry& entry = this->getEntryByIndex(entryIndex);
    entry.isControlStructure = true;
    entry.controlVariableIndex = controlVariableIndex;
//    entry.controlStructureType = controlStructureType;
    return entryIndex;
}
