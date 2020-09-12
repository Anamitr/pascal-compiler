#include "Decoder.h"



string Decoder::decodeSign(int signCode) {
    cout << "Decoder::decodeSign\t\t\t\t\tsignCode: " << signCode << endl;
    switch (signCode) {
        case PLUS:
            return "add";
        case MINUS:
            return "sub";
        case MULTIPLICATION:
            return "mul";
        case DIVISION:
            return "div";
        case MOD:
            return "mod";
        case AND:
            return "and";
        case OR:
            return "or";
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
        case REAL_TO_INT:
            return "realtoint";
        default:
            cout << "!-Decoder::getConversionStringFromCode\tNo such conversion type "
                 << conversionCode << "!" << endl;
            exit(-1);
    }
}

int Decoder::getConversionResultType(int conversionCode) {
    switch (conversionCode) {
        case INT_TO_REAL:
            return REAL;
        case REAL_TO_INT:
            return INTEGER;
        default:
            cout << "!-Decoder::getConversionResultType\tNo such conversion type "
                 << conversionCode << "!" << endl;
            exit(-1);
    }
}

int Decoder::getConversionCodeFromEntriesTypes(int oldType, int newType) {
    if (oldType == INTEGER && newType == REAL) return INT_TO_REAL;
    if (oldType == REAL && newType == INTEGER) return REAL_TO_INT;
    else {
        cout << "!-Decoder::getConversionCodeFromEntriesTypes\t"
             << "No such conversion type from " << oldType << " to "
             << newType << "!" << endl;
        exit(-1);
    }
}

string Decoder::getTokenTypeStringFromCode(int tokenTypeCode) {
    switch (tokenTypeCode) {
        case ID:
            return "ID";
        case NUM:
            return "NUM";
        case IF:
            return "IF";
        case WHILE:
            return "WHILE";
        default:
            cout << "No such tokenTypeCode: " << tokenTypeCode << "!\n";
            exit(-1);
    }
}

constexpr unsigned int Decoder::str2int(const char *str, int h) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

string Decoder::getRelopOperationFromString(string relopSign) {
    const char *relopSingCStr = relopSign.c_str();
    switch (str2int(relopSingCStr)) {
        case str2int("<"):
            return "jl";
        default:
            cout << "!-Decoder::getRelopOperationFromString\t" << "No such relop sign "
                 << relopSign << "!" << endl;
            exit(-1);
    }
}

string Decoder::getRelopCommandStringFromCode(int relopCode) {
    switch (relopCode) {
        case EQUAL:
            return "je";
        case LOWER:
            return "jl";
        default:
            cout << "!-Decoder::getRelopCommandStringFromCode\t" << "No such relop sign "
                 << relopCode << "!" << endl;
    }
}

