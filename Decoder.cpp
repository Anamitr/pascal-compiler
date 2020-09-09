#include "Decoder.h"

string Decoder::decodeSign(int signCode) {
    switch (signCode) {
        case PLUS:
            return "add";
        case MINUS:
            return "sub";
        default:
            cout << "No such sign!" << endl;
            exit(-1);
    }
}

int Decoder::getVarTypeSize(int typeCode) {
    switch (typeCode) {
        case INTEGER:
            return 4;
        case REAL:
            return 8;
        default:
            cout << "No such typeCode " << typeCode << "!" << endl;
            exit(-1);
    }
}

string Decoder::getShortTypeSignFromCode(int typeCode) {
    switch (typeCode) {
        case INTEGER:
            return "i";
        case REAL:
            return "r";
        default:
            cout << "No such typeCode " << typeCode << "!" << endl;
            exit(-1);
    }
}


string Decoder::getConversionStringFromCode(int conversionCode) {
    switch (conversionCode) {
        case INT_TO_REAL:
            return "inttoreal";
        default:
            cout << "No such conversion type " << conversionCode << "!" << endl;
            exit(-1);
    }
}

int Decoder::getConversionResultType(int conversionCode) {
    switch (conversionCode) {
        case INT_TO_REAL:
            return REAL;
        default:
            cout << "No such conversion type " << conversionCode << "!" << endl;
            exit(-1);
    }
}

int Decoder::getConversionCodeFromEntriesTypes(int oldType, int newType) {
    if (oldType == INTEGER && newType == REAL) return INT_TO_REAL;
    else {
        cout << "No such conversion type from " << oldType << " to " << newType << "!" << endl;
        exit(-1);
    }
}
