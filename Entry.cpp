
#include "Entry.h"

string Entry::getPosInMemString() {
    if (this->isFunction) {
        return "*BP+" + to_string(this->BPOffset);
    } else if (this->isLocal) {
        return "BP" + to_string(this->BPOffset);
    } else if (this->isPointer) {
        if (isGlobal) {

        } else {
            return "${" + this->name + "-memAddr}";
        }
    } else if (this->isConstant) {
        return "#" + name;
    } else {
        return to_string(positionInMemory);
    }
}

void Entry::assignType(int typeCode) {
    this->typeCode = typeCode;
    this->typeChar = Decoder::getShortTypeSignFromCode(typeCode);
    this->shortenIfReal();
}

ostream &operator<<(ostream &os, const Entry &entry) {
    os << "indexInSymbolTable: " << entry.indexInSymbolTable << " tokenTypeCode: " << entry.tokenTypeCode
       << " typeCode: " << entry.typeCode << " positionInMemory: " << entry.positionInMemory << " BPOffset: "
       << entry.BPOffset << " name: " << entry.name << " typeChar: " << entry.typeChar << " posInMemoryString: "
       << entry.posInMemoryString << " isVariable: " << entry.isVariable << " isFunction: " << entry.isFunction
       << " isProcedure: " << entry.isProcedure << " isConstant: " << entry.isConstant << " isPointer: "
       << entry.isPointer << " isLocal: " << entry.isLocal << " memAllocSize: " << entry.memAllocSize
       << " numOfPointers: " << entry.numOfPointers << " subprogramArgumentsIndexes: ";
    for (int argIndex : entry.subprogramArgumentsIndexes) {
        cout << argIndex << ", ";
    }
    cout << endl;
    return os;
}

string Entry::getNameWithTypeString() {
    return this->name + "(" + this->typeChar + ")";
}

string Entry::getNameWithTokenTypeString() {
    return this->name + "(" + Decoder::getTokenTypeStringFromCode(this->tokenTypeCode) + ")";
}

void Entry::shortenIfReal() {
    if (this->typeCode == REAL) {
        cout << "Entry::shortenIfReal" << endl;
        this->name.erase(this->name.find_last_not_of('0') + 1, std::string::npos);
        if (this->name.back() == '.') {
            this->name = this->name.substr(0, this->name.size() - 1);
        }

    }
}

