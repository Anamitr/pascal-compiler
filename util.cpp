//
// Created by konrad on 9/10/20.
//

#include "util.h"

bool replaceInString(std::string& str, const std::string& from, const std::string& to) {

    size_t index = 0;
    while (true) {
        /* Locate the substring to replace. */
        index = str.find(from, index);
        if (index == std::string::npos) break;

        /* Make the replacement. */
        str.replace(index, from.length(), to);

        /* Advance index forward so the next iteration doesn't pick it up as well. */
        index += from.length();
    }
    return true;
}

Entry getStubLiteralEntry(string name, int typeCode){
    Entry entry;
    entry.isConstant = true;
    entry.name = name;
    entry.assignType(typeCode);
//    entry.shortenIfReal();
    return entry;
}