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

const RegisterFile& CPU::getRegisters() const { return m_registers; }

void CPU::runUntilHalt()
{
    while( !m_halted  )
    {
        step(); 
    }
}

void CPU::execute( const Instruction& m_inst ) 
{
    int reg{ m_inst.getRegisterIndex() };
    int address{ m_inst.getAddressOrValue() };
    char op{ m_inst.getOpCode() }; 
    
    switch( op )
    {
        case '1': 
            m_registers.setRegister( reg, m_memory.read(address)); 
            break; 

        case '2': 
        {
            char hexChars[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; 
            int highDigit{ address / 16 }; 
            int lowDigit{ address % 16 }; 
            std::string hexString { "" }; 
            hexString += hexChars[ highDigit ]; 
            hexString += hexChars[ lowDigit ]; 
            m_registers.setRegister( reg, hexString ); 
            break; 
        }

        case '3': 
        m_memory.write( address, m_registers.getRegister( reg )); 
        break; 

        case 'C': 
        m_halted = true; 
        return; 

        default: 
            break;

        }

        if( !m_halted )
            m_pc += 2; 
}

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
