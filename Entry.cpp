
#include "Entry.h"

string Entry::getPosInMemString() {
    if(this->isFunction) {
        return "*BP+" + to_string(this->BPOffset);
    } else {
        return to_string(positionInMemory);
    }
}
