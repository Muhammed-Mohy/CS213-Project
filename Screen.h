#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include <vector>

class Screen {
public:
    enum MenuInputResult {
        InvalidMenuChoice = -1,
        EndOfInput = -2
    };

    Screen(std::istream& input = std::cin,
           std::ostream& output = std::cout);

    void showMainMenu() const;
    int promptMenuChoice() const;
    std::string promptLine(const std::string& prompt) const;

    void displayMemory(const std::vector<std::string>& memory) const;
    void displayMachineState(
        int pc,
        const std::string& ir,
        const std::vector<std::string>& registers) const;

    void appendMachineOutput(const std::string& text);
    void displayMachineOutput() const;
    void clearMachineOutput();

    void showStatus(const std::string& message) const;
    void showError(const std::string& message) const;

private:
    std::istream& m_input;
    std::ostream& m_output;
    std::string m_machineOutput;
};

#endif
