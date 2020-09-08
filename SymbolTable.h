//
// Created by konrad on 9/8/20.
//

#pragma once

#include "global.h"

using namespace std;

class SymbolTable {
public:
    int lookup(const string);
    int insert(const string, int typeOfToken);

};

