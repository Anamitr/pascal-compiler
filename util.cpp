//
// Created by konrad on 9/10/20.
//

#include "util.h"

bool replaceInString(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

Entry getStubLiteralEntry(string name, int typeCode){
    Entry entry;
    entry.isConstant = true;
    entry.name = name;
    entry.assignType(typeCode);
    return entry;
}