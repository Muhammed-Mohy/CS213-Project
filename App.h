#ifndef APP_H
#define APP_H

#include <cstddef>
#include <string>
#include <vector>

class Screen;

// The small set of machine operations used by the user interface.
// A future VoleMachine can implement this interface.
class VoleMachineInterface {
public:
    virtual ~VoleMachineInterface() {}

    virtual bool loadProgram(
        const std::vector<std::string>& instructions,
        int startAddress = 0) = 0;
    virtual void run() = 0;
    virtual void step() = 0;
    virtual bool isHalted() const = 0;

    virtual int getPC() const = 0;
    virtual std::string getIR() const = 0;
    virtual std::vector<std::string> getRegisters() const = 0;
    virtual std::vector<std::string> getMemoryValues() const = 0;

    // Returns all printable machine output produced by the current program.
    virtual std::string getMachineOutput() const = 0;
};

class App {
public:
    App(Screen& screen, VoleMachineInterface& machine);

    void run();

private:
    void handleChoice(int choice);
    void loadProgram();
    void runProgram();
    void stepInstruction();
    void displayMachineState();
    void displayNewMachineOutput();

    Screen& m_screen;
    VoleMachineInterface& m_machine;
    bool m_running;
    std::size_t m_displayedOutputLength;
};

#endif
