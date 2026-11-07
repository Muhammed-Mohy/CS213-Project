#include "Instruction.h"
#include <cctype>
#include <sstream>

Instruction::Instruction(const std::string& raw) {
    rawInstruction = raw;
    if (isValid()) {
        opCode = raw[0];

        std::stringstream ss1;
        ss1 << std::hex << raw[1];
        ss1 >> registerIndex;

        std::stringstream ss2;
        ss2 << std::hex << raw.substr(2, 2);
        ss2 >> addressOrValue;
    } else {
        opCode = '\0';
        registerIndex = 0;
        addressOrValue = 0;
    }
}

bool Instruction::isValid() const {
    if (rawInstruction.length() != 4) return false;
    for (char c : rawInstruction) {
        if (!isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

char Instruction::getOpCode() const { return opCode; }
int Instruction::getRegisterIndex() const { return registerIndex; }
int Instruction::getAddressOrValue() const { return addressOrValue; }
std::string Instruction::getRawInstruction() const { return rawInstruction; }