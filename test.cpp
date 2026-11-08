#include <iostream>
#include <string>

// Temporary place holders
class Instruction 
{
public:
    char getOpcode() const { return ' '; }
    int getR() const { return 0; }
    int getS() const { return 0; }
    int getT() const { return 0; }
    int getAddressXY() const { return 0; }
    int getRotateCount() const { return 0; }
    bool isHalt() const { return false; }
};

class RegisterFile 
{
public:
    std::string read(int index) { return ""; }
    void write(int index, std::string value) {}
    void reset() {}
};

class ALU 
{
public:
    std::string addTwoComplement(std::string a, std::string b) { return "0"; }
};

class ControlUnit 
{
public:
    Instruction parse(std::string rawIR) { return Instruction{}; }
    bool validate(const Instruction& inst) { return true; }
};

class Memory 
{
public:
    std::string readWord(int address) { return "C000"; }
};

class CPU
{
public:
    CPU(Memory& memory); 
    void reset(int startAddress); 
    void fetch(); 
    Instruction decode(); 
    void execute( const Instruction& m_inst ); 
    void step(); 
    void runUntilHalt(); 
    bool isHalted() const; 
    int getPC() const; 
    const std::string& getIR() const; 
    const RegisterFile& getRegisters(); 

private:
    int m_pc{}; 
    std::string m_ir{}; 
    bool m_halted{}; 
    RegisterFile m_registers{}; 
    ALU m_alu{}; 
    ControlUnit m_controlUnit{}; 
    Memory& m_memory; 

};

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


int main()
{
    Memory memory{};

    CPU cpu{ memory };

    cpu.reset(0x20);
    cpu.fetch();

    std::cout << "PC: " << cpu.getPC() << '\n';
    std::cout << "IR: " << cpu.getIR() << '\n';
    std::cout << "Halted: " << std::boolalpha << cpu.isHalted() << '\n';

    return 0;
}