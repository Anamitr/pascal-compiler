#pragma once

#include "global.h"

using namespace std;

class Entry {
public:
    int position;
    string name;
    int type;

    bool isVariable = false;
};
