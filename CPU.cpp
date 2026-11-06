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

const RegisterFile& CPU::getRegisters() { return m_registers; }

void CPU::runUntilHalt()
{
    while( !m_halted  )
    {
        step(); 
    }
}

void CPU::execute( const Instruction& m_inst ) {}

Instruction CPU::decode()
{
    return m_controlUnit.parse(m_ir); 
}

void CPU::step()
{
    fetch(); 
    Instruction m_inst = decode(); 
    if( !m_controlUnit.validate( m_inst ) )
    {
        m_halted = true; 
        return; 
    }

    execute( m_inst ); 
}
