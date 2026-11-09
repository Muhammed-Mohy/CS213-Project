#include "RegisterFile.h"
#include <iostream>

RegisterFile::RegisterFile() {
    regs.resize(COUNT, "00");
}

std::string RegisterFile::read(int index) const {
    if (index >= 0 && index < COUNT)
        return regs[index];

    return "00";
}

void RegisterFile::write(int index, const std::string& value) {
    if (index >= 0 && index < COUNT)
        regs[index] = value;
}

void RegisterFile::reset() {
    for (int i = 0; i < COUNT; ++i)
        regs[i] = "00";
}

void RegisterFile::display() const {
    for (int i = 0; i < COUNT; ++i)
    {
        std::cout << "R" << i << ": " << regs[i] << '\n';
    }
}
