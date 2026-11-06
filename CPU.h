#ifndef CPU_H
#define CPU_H

#include "Instruction.h"
#include "ControlUnit.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "ALU.h"
#include <string>

class CPU
{
public:
    CPU(Memory& memory); 
    void reset(int startAddress); 
    void fetch(); 
    Instruction decode(); 
    void execute( const Instruction& inst ); 
    void step(); 
    void runUntilHalt(); 
    bool isHalted() const; 
    int getPC() const; 
    const std::string& getIR() const; 
    const RegisterFile& getRegisters() const; 

private:
    int m_pc{}; 
    std::string m_ir{}; 
    bool m_halted{}; 
    RegisterFile m_registers{}; 
    ALU m_alu{}; 
    ControlUnit m_controlUnit{}; 
    Memory& m_memory; 

};

#endif
