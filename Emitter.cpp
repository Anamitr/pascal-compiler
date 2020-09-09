#include "Emitter.h"


Emitter emitter = Emitter();

void Emitter::emitString(string stringToEmit) {
    output.append(stringToEmit);
    output.append("\n");
}

void Emitter::writeToFile(string outputFileName) {
    ofstream outputStream(outputFileName);
    outputStream << output;
    outputStream.close();
}

void Emitter::generateOperation(int operationCode, int firstVarIndex, int secondVarIndex) {
    string operation = Decoder::decodeSign(operationCode);
    cout << "Got operation: " << operation << endl;

}
