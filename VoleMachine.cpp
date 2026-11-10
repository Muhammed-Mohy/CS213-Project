#include "VoleMachine.h"
#include <iostream>

VoleMachine::VoleMachine()
    : m_memory { m_screen }
    , m_cpu { m_memory }
    {

    }

void VoleMachine::menu()
{
    bool running = true;
    while (running)
    {
        std::cout << "====================\n";
        std::cout << "Vole Machine Simulator\n";
        std::cout << "====================\n";
        std::cout << "1. Load a new program\n";
        std::cout << "2. Overwrite memory cell\n";
        std::cout << "3. Overwrite register\n";
        std::cout << "4. Run all\n";
        std::cout << "5. Run step\n";
        std::cout << "6. Display state\n";
        std::cout << "7. Exit\n";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                std::cout << "Enter file name and start address (hex): ";
                std::string filePath;
                int startAddress = 0;
                std::cin >> filePath;
                std::cin >> std::hex >> startAddress;
                std::cin >> std::dec;
                loadNewProgram(filePath, startAddress);
                break;
            }
            case 2:
            {
                std::cout << "Enter address (hex) and value: ";
                int address = 0;
                std::string value;
                std::cin >> std::hex >> address;
                std::cin >> std::dec;
                std::cin >> value;
                overwriteMemory(address, value);
                break;
            }
            case 3:
            {
                int index = 0;
                std::string value;
                std::cin >> std::hex >> index;
                std::cin >> std::dec;
                std::cin >> value;
                overwriteRegister(index, value);
                break;
            }
            case 4:
                runAll();
                running = askExitOrLoadAnother();
                break;
            case 5:
                runStepByStep();
                running = askExitOrLoadAnother();
                break;
            case 6:
                displayState();
                break;
            case 7:
                running = false;
                break;
            default:
                break;
        }
    }
}

void VoleMachine::loadNewProgram(const std::string& filePath, int startAddress)
{
    if( !m_memory.isValidInstructionAddress( startAddress ) )
    {
        std::cout << "Error: start address must be even and less than FF\n";
        return;
    }    
    
    if (!m_memory.isValidInstructionAddress(startAddress))
        return;

    m_memory.clear();
    m_memory.loadFromFile(filePath, startAddress);
    m_cpu.reset(startAddress);
    displayState();
}

void VoleMachine::overwriteMemory( int address, const std::string& value )
{
    if( !m_memory.isValidAddress( address ) )
        return; 

    m_memory.write( address, value ); 
}

void VoleMachine::overwriteRegister( int index, const std::string& value )
{   
    if (index < 0 || index > 15)
        return;
    m_cpu.getRegisters().write( index, value ); 
}

void VoleMachine::runAll()
{
    m_cpu.runUntilHalt(); 
    displayState(); 
}

void VoleMachine::runStepByStep()
{
    std::cin.ignore( 10000, '\n' );
    while( !m_cpu.isHalted() )
    {
        m_cpu.step();
        displayState();
        if( m_cpu.isHalted() )
            break;

        std::cout << "Press Enter to run the next step\n";
        std::string enter;
        std::getline( std::cin, enter );
    }
}

void VoleMachine::displayState()
{
    m_memory.displayMatrix();

    int pc = m_cpu.getPC();
    std::cout << "PC: " << std::hex << std::uppercase;
    if( pc < 16 )
        std::cout << '0';
    std::cout << pc << std::dec << '\n';

    std::cout << "IR: " << m_cpu.getIR() << '\n';
    m_cpu.getRegisters().display();

    std::cout << "Screen: ";
    m_screen.display();
}

bool VoleMachine::askExitOrLoadAnother()
{
    std::cout << "1. Load another program\n";
    std::cout << "2. Exit\n";

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return choice == 1;
}