#include "Instruction.h"
#include <cctype>
#include <sstream>

Instruction::Instruction(const std::string& rawInstruction) {
    raw = rawInstruction;
    if (isValid()) {
        opcode = raw[0];
        
        std::stringstream ss1;
        ss1 << std::hex << raw[1];
        ss1 >> r;

        std::stringstream ss2;
        ss2 << std::hex << raw[2];
        ss2 >> s;

        std::stringstream ss3;
        ss3 << std::hex << raw[3];
        ss3 >> t;
    } else {
        opcode = '\0';
        r = 0;
        s = 0;
        t = 0;
    }
}

bool Instruction::isValid() const {
    if (raw.length() != 4) return false;
    for (char c : raw) {
        if (!isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool Instruction::isHalt() const {
    return raw == "C000" || opcode == 'C' || opcode == 'c';
}

std::string Instruction::getRaw() const { return raw; }
char Instruction::getOpcode() const { return opcode; }
int Instruction::getR() const { return r; }
int Instruction::getS() const { return s; }
int Instruction::getT() const { return t; }


int Instruction::getAddressXY() const {
    int val = 0;
    std::stringstream ss;
    ss << std::hex << raw.substr(2, 2);
    ss >> val;
    return val;
}

int Instruction::getRotateCount() const {
    return t; 
}