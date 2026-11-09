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

RegisterFile& CPU::getRegisters() { return m_registers; }

const RegisterFile& CPU::getRegisters() const { return m_registers; }

void CPU::runUntilHalt()
{
    int steps{ 0 }; 
    while( !m_halted && steps < 65536 )
    {
        step(); 
        ++steps; 
    }
    if( !m_halted )
        m_halted = true; 
}

void CPU::execute( const Instruction& inst ) 
{
    int reg{ inst.getR() };
    int address{ inst.getAddressXY() };
    char op{ inst.getOpcode() }; 
    if( op >= 'a' && op <= 'z' )
        op = static_cast<char>(op - 32); 
    
    switch( op )
    {
        case '1': 
            m_registers.write( reg, m_memory.read(address)); 
            break; 

        case '2': 
        {
            char hexChars[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; 
            int highDigit{ address / 16 }; 
            int lowDigit{ address % 16 }; 
            std::string hexString { "" }; 
            hexString += hexChars[ highDigit ]; 
            hexString += hexChars[ lowDigit ]; 
            m_registers.write( reg, hexString ); 
            break; 
        }

        case '3': 
        m_memory.write( address, m_registers.read( reg )); 
        break; 

        case '4': 
        {
            int s{ inst.getS() }; 
            int t{ inst.getT() }; 
            m_registers.write( t, m_registers.read(s) ); 
            break; 
        }

        case '5': 
        {
            int s{ inst.getS() };
            int t{ inst.getT() };
            m_registers.write( reg, m_alu.addTwoComplement( m_registers.read(s), m_registers.read(t) ) );
            break;
        }

        case '6': 
        {
            int s{ inst.getS() };
            int t{ inst.getT() };
            m_registers.write( reg, m_alu.addFloatingPoint( m_registers.read(s), m_registers.read(t) ) );
            break;
        }

        case '7': 
        {
            int s{ inst.getS() };
            int t{ inst.getT() };
            m_registers.write( reg, m_alu.bitwiseOr( m_registers.read(s), m_registers.read(t) ) );
            break;
        }

        case '8': 
        {
            int s{ inst.getS() };
            int t{ inst.getT() };
            m_registers.write( reg, m_alu.bitwiseAnd( m_registers.read(s), m_registers.read(t) ) );
            break;
        }

        case '9': 
        {
            int s{ inst.getS() };
            int t{ inst.getT() };
            m_registers.write( reg, m_alu.bitwiseXor( m_registers.read(s), m_registers.read(t) ) );
            break;
        }

        case 'A': 
        {
            int times{ inst.getRotateCount() }; 
            m_registers.write( reg, m_alu.rotateRight( m_registers.read(reg), times) ); 
            break; 
        }

        case 'B': 
        {
            if( m_registers.read(reg) == m_registers.read(0) )
            {
                m_pc = address; 
                return; 
            }
            break; 
        }

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
    if( m_halted )
        return; 

    fetch(); 
    Instruction inst = decode(); 
    if( !m_controlUnit.validate( inst ) )
    {
        m_halted = true; 
        return; 
    }

    execute( inst ); 
}
