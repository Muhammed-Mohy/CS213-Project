#ifndef CONTROLUNIT_
#define CONTROLUNIT_

#include "Instruction.h"
#include <string> 

class ControlUnit
{
public: 
    Instruction parse( const std::string& rawR ); 
    bool validate( const Instruction& inst ); 
}; 

#endif