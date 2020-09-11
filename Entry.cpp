
#include "Entry.h"

string Entry::getPosInMemString() {
    if(this->isFunction) {
        return "*BP+" + to_string(this->BPOffset);
    } else if (this->isLocal) {
        return "BP" + to_string(this->BPOffset);
    } else if (this->isPointer) {
        return "${" + this->name + "-memAddr}";
    } else if(this->isConstant) {
        return "#" + name;
    } else {
        return to_string(positionInMemory);
    }
}

void Entry::assignType(int typeCode) {
    this->typeCode = typeCode;
    this->typeChar = Decoder::getShortTypeSignFromCode(typeCode);
}
