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
    entry.type = typeOfToken;
    entry.name = name;
    entries.push_back(entry);
    int p = entries.size() - 1;
    cout << "Added entry with name " << name << " and type " << typeOfToken
         << " at position " << p << endl;

    return p;
}

void SymbolTable::addGlobalVariablesWithType(list<int> idList, int type) {
    for (int id : idList) {
        cout << id << ", ";
    }
    cout << endl;
//    cout << "ids: " << idList << endl;
}
