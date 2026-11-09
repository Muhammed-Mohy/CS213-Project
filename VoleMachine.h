#ifndef VOLE_MACHINE_H
#define VOLE_MACHINE_H

#include <string>
#include "CPU.h"
#include "Memory.h"
#include "Screen.h"

class VoleMachine {
private:
    // This order matters: memory uses screen, and CPU uses memory.
    Screen screen;
    Memory memory;
    CPU cpu;
    bool programLoaded = false;

public:
    VoleMachine();

    void menu();
    void loadNewProgram(const std::string& filePath, int startAddress);
    void overwriteMemory(int address, const std::string& value);
    void overwriteRegister(int index, const std::string& value);
    void runAll();
    void runStepByStep();
    void displayState() const;
    bool askExitOrLoadAnother();
};
#endif