#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

class Instruction {
private:
    std::string raw;     
    char opcode;        
    int r;            
    int s;              
    int t;               

public:
    Instruction(const std::string& rawInstruction);

    bool isValid() const;
    bool isHalt() const;

    std::string getRaw() const;
    char getOpcode() const;
    int getR() const;
    int getS() const;
    int getT() const;
    int getAddressXY() const;
    int getRotateCount() const;
};

#endif 