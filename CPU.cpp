#include "CPU.h"

CPU::CPU(Memory& memory)
    : m_memory { memory }
    {

    }

void CPU::reset(int startAddress)
{
    m_pc = startAddress; 
    m_ir = ""; 
    m_halted = false; 
    m_registers.reset(); 
}

void CPU::fetch()
{
    m_ir = m_memory.readWord(m_pc); 
}

bool CPU::isHalted() const { return m_halted; }

int CPU::getPC() const { return m_pc; }

const std::string& CPU::getIR() const { return m_ir; }

RegisterFile CPU::getRegisters() { return m_registers; }

void CPU::runUntilHalt()
{
    while( !m_halted  )
    {
        step(); 
    }
}

void CPU::step() {}

Instruction CPU::decode() { return Instruction{}; }

void CPU::execute( const Instruction& m_inst ) {}

