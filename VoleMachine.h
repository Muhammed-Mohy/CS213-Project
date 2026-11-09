#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <string>
#include "Screen.h"
#include "Memory.h"
#include "CPU.h"

using namespace std;

class VoleMachine {
private:
    Screen screen;
    Memory memory;
    CPU cpu;
public:
    VoleMachine();

    void menu();
    void loadNewProgram(const string& filePath, int startAddress);
    void runAll();
    void runStepByStep();
    void displayState() const;
    void overwriteMemory(int address, const string& value);
    void overwriteRegisterIndex(int index, const string& value);
       
    bool askExitOrLoadAnother();
};
#endif