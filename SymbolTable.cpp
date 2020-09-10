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
    cout << "Added entry with name " << name << " and tokenTypeCode " <<
         Decoder::getTokenTypeStringFromCode(typeOfToken) << " at index " << p << endl;
    return p;
}

void SymbolTable::addGlobalVariablesWithType(list<int> indexList, int typeCode) {
    string idsMsg = "";
    idsMsg.append("SymbolTable::addGlobalVariablesWithType indexList: ");
    for (int index : indexList) {
        idsMsg.append(to_string(index) + ", ");
        assignVariableItsType(entries.at(index), typeCode);
        entries[index].positionInMemory = freeMemoryPointer;
        cout << "Variable " << entries[index].name << " allocated at " << freeMemoryPointer << endl;
        freeMemoryPointer += Decoder::getVarTypeSize(typeCode);
    }
    idsMsg.append("\n");
    cout << idsMsg;
//    cout << "ids: " << indexList << endl;
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
    list<int> ids;
    ids.push_back(p);
    addGlobalVariablesWithType(ids, typeCode);
    return this->getEntryByIndex(p);
}

Entry SymbolTable::allocateFunReturnVarPointer(Entry& functionEntry) {
    cout << "SymbolTable::allocateFunReturnVarPointer: " + functionEntry.name +
            " - " + functionEntry.typeChar << endl;
    functionEntry.BPOffset = BPOffsetPointer;
    BPOffsetPointer += Decoder::getVarTypeSize(functionEntry.typeCode);
    return Entry();
}
