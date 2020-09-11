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
    if (typeCode != -1) assignVariableItsType(entry, typeCode);
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
        assignVariableItsType(entries.at(index), typeCode);
        entries[index].positionInMemory = freeMemoryPointer;
        cout << "\t\t\t\t\t\tVariable " << entries[index].name << " allocated at " << freeMemoryPointer << endl;
        freeMemoryPointer += Decoder::getVarTypeSize(typeCode);
    }
    idsMsg.append("\n");
    cout << idsMsg;
}


void SymbolTable::assignVariableItsType(Entry &entry, int typeCode) {
    entry.typeCode = typeCode;
    entry.typeChar = Decoder::getShortTypeSignFromCode(typeCode);
}

Entry &SymbolTable::getEntryByIndex(int index) {
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
    functionEntry.BPOffset = BPOffsetPointer;
    BPOffsetPointer += Decoder::getVarTypeSize(functionEntry.typeCode);
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
        entry.BPOffset = this->BPOffsetPointer;
        BPOffsetPointer += Decoder::getVarTypeSize(entry.typeCode);
        entry.posInMemoryString = "*BP+" + to_string(entry.BPOffset);
        result.push_back(entry);
        cout << "SymbolTable::assignPointerAddresses\t\t" << entry.name << ", " <<
             entry.posInMemoryString << endl;
    }
    return result;
}
