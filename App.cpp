#include "App.h"

#include "Screen.h"

#include <sstream>

App::App(Screen& screen, VoleMachineInterface& machine)
    : m_screen(screen),
      m_machine(machine),
      m_running(false),
      m_displayedOutputLength(0)
{
}

void App::run()
{
    m_running = true;

    while (m_running) {
        m_screen.showMainMenu();
        const int choice = m_screen.promptMenuChoice();
        handleChoice(choice);
    }
}

void App::handleChoice(int choice)
{
    switch (choice) {
    case 0:
        m_screen.showStatus("Exiting.");
        m_running = false;
        break;
    case 1:
        loadProgram();
        break;
    case 2:
        runProgram();
        break;
    case 3:
        stepInstruction();
        break;
    case 4:
        displayMachineState();
        break;
    case Screen::InvalidMenuChoice:
        m_screen.showError("Invalid menu choice. Choose a number from 0 to 4.");
        break;
    case Screen::EndOfInput:
        m_screen.showStatus("End of input. Exiting.");
        m_running = false;
        break;
    default:
        m_screen.showError("Invalid menu choice. Choose a number from 0 to 4.");
        break;
    }
}

void App::loadProgram()
{
    const std::string programText = m_screen.promptLine(
        "Enter instruction words separated by spaces (blank cancels): ");
    std::istringstream programStream(programText);
    std::vector<std::string> instructions;
    std::string instruction;

    while (programStream >> instruction) {
        instructions.push_back(instruction);
    }

    if (instructions.empty()) {
        m_screen.showStatus("Program loading cancelled.");
        return;
    }

    if (!m_machine.loadProgram(instructions, 0)) {
        m_screen.showError("The program could not be loaded.");
        return;
    }

    m_screen.clearMachineOutput();
    m_displayedOutputLength = 0;
    m_screen.showStatus("Program loaded.");
}

void App::runProgram()
{
    if (m_machine.isHalted()) {
        m_screen.showStatus("The machine is halted. Load a program to continue.");
        return;
    }

    m_machine.run();
    displayNewMachineOutput();

    if (m_machine.isHalted()) {
        m_screen.showStatus("Program halted.");
    } else {
        m_screen.showStatus("Run finished.");
    }
}

void App::stepInstruction()
{
    if (m_machine.isHalted()) {
        m_screen.showStatus("The machine is halted. Load a program to continue.");
        return;
    }

    m_machine.step();
    displayNewMachineOutput();

    if (m_machine.isHalted()) {
        m_screen.showStatus("Machine halted.");
    } else {
        m_screen.showStatus("Instruction stepped.");
    }
}

void App::displayMachineState()
{
    m_screen.displayMachineState(
        m_machine.getPC(),
        m_machine.getIR(),
        m_machine.getRegisters());
    m_screen.displayMemory(m_machine.getMemoryValues());
}

void App::displayNewMachineOutput()
{
    const std::string machineOutput = m_machine.getMachineOutput();

    // A shorter output means the machine was reset outside this App.
    if (machineOutput.size() < m_displayedOutputLength) {
        m_displayedOutputLength = 0;
        m_screen.clearMachineOutput();
    }

    if (machineOutput.size() == m_displayedOutputLength) {
        return;
    }

    const std::string newOutput =
        machineOutput.substr(m_displayedOutputLength);

    // Screen displays its entire buffer, so keep only the newly produced
    // portion here. This prevents earlier output from being printed again.
    m_screen.clearMachineOutput();
    m_screen.appendMachineOutput(newOutput);
    m_screen.displayMachineOutput();
    m_displayedOutputLength = machineOutput.size();
}
