#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include "Memory.h"
#include "CPU.h"
#include "Screen.h"
#include <string>

class VoleMachine
{
public:
    VoleMachine(); 
    void menu(); 
    void loadNewProgram( const std::string& filePath, int startAddress ); 
    void overwriteMemory( int address, const std::string& value ); 
    void overwriteRegister( int index, const std::string& value ); 
    void runAll(); 
    void runStepByStep(); 
    void displayState(); 
    bool askExitOrLoadAnother(); 

private:
    Screen m_screen{}; 
    Memory m_memory; 
    CPU m_cpu; 

};

#endif