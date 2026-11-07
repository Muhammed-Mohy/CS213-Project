#include "RegisterFile.h"

RegisterFile::RegisterFile() {

    registers.resize(16, "00");
}

void RegisterFile::setRegister(int index, const std::string& value) {
    if (index >= 0 && index < 16) {
        registers[index] = value;
    }
}

std::string RegisterFile::getRegister(int index) const {
    if (index >= 0 && index < 16) {
        return registers[index];
    }
    return "00";
}

void RegisterFile::reset() {
    for (int i = 0; i < 16; ++i) {
        registers[i] = "00";
    }
}