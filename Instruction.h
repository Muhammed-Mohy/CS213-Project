#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

class Instruction {
private:
    std::string rawInstruction;
    char opCode;
    int registerIndex;
    int addressOrValue;

public:
    Instruction(const std::string& raw);

    bool isValid() const;
    char getOpCode() const;
    int getRegisterIndex() const;
    int getAddressOrValue() const;
    std::string getRawInstruction() const;
};

#endif