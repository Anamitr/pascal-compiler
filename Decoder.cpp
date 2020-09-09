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
