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

int SymbolTable::insert(const string name, int typeOfToken) {
    Entry entry = Entry();
    entry.typeCode = typeOfToken;
    entry.name = name;
    int p = entries.size();
    entry.indexInSymbolTable = p;
    entries.push_back(entry);
    cout << "Added entry with name " << name << " and typeCode " << typeOfToken
         << " at index " << p << endl;
    return p;
}

void SymbolTable::addGlobalVariablesWithType(list<int> idList, int typeCode) {
    string idsMsg = "";
    idsMsg.append("SymbolTable::addGlobalVariablesWithType idList: ");
    for (int id : idList) {
        idsMsg.append(to_string(id) + ", ");
        entries[id].typeCode = typeCode;
        entries[id].typeChar = Decoder::getShortTypeSignFromCode(typeCode);
        entries[id].positionInMemory = freeMemoryPointer;
        cout << "Variable " << entries[id].name << " allocated at " << freeMemoryPointer << endl;
        freeMemoryPointer += Decoder::getVarTypeSize(typeCode);
    }
    idsMsg.append("\n");
    cout << idsMsg;
//    cout << "ids: " << idList << endl;
}


Entry SymbolTable::getEntryByIndex(int index) {
    return entries[index];
}

Entry SymbolTable::allocateTempVarOfType(int typeCode) {
    int p = this->insert("t" + to_string(tempVarCounter++), ID);
    list<int> ids;
    ids.push_back(p);
    addGlobalVariablesWithType(ids, typeCode);
    return this->getEntryByIndex(p);
}
