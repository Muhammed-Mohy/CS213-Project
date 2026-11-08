#include "Screen.h"

#include <iomanip>
#include <sstream>

Screen::Screen(std::istream& input, std::ostream& output)
    : content(),
      m_input(input),
      m_output(output)
{
}

void Screen::write(std::string value)
{
    content += value;
}

std::string Screen::read() const
{
    return content;
}

void Screen::display() const
{
    m_output << content;
}

void Screen::clear()
{
    content.clear();
}

void Screen::showMainMenu() const
{
    m_output << "\n=== Vole Machine Simulator ===\n"
             << "1. Load a program\n"
             << "2. Run the program\n"
             << "3. Step one instruction\n"
             << "4. Display machine state\n"
             << "0. Exit\n";
}

int Screen::promptMenuChoice() const
{
    m_output << "Enter your choice: ";
    m_output.flush();

    std::string line;
    if (!std::getline(m_input, line)) {
        return EndOfInput;
    }

    std::istringstream choiceStream(line);
    int choice;

    if (!(choiceStream >> choice) || choice < 0 || choice > 4) {
        return InvalidMenuChoice;
    }

    char extraCharacter;
    if (choiceStream >> extraCharacter) {
        return InvalidMenuChoice;
    }

    return choice;
}

std::string Screen::promptLine(const std::string& prompt) const
{
    m_output << prompt;
    m_output.flush();

    std::string line;
    if (!std::getline(m_input, line)) {
        return std::string();
    }

    return line;
}

void Screen::displayMemory(const std::vector<std::string>& memory) const
{
    m_output << "\n=== Memory ===\n";
    for (std::size_t address = 0; address < memory.size(); ++address) {
        m_output << "0x" << std::uppercase << std::hex
                 << std::setfill('0') << std::setw(2) << address
                 << std::dec << std::nouppercase << std::setfill(' ')
                 << ": "
                 << memory[address] << '\n';
    }
}

void Screen::displayMachineState(
    int pc,
    const std::string& ir,
    const std::vector<std::string>& registers) const
{
    m_output << "\n=== Machine State ===\n"
             << "PC: " << pc << '\n'
             << "IR: " << (ir.empty() ? "(empty)" : ir) << '\n'
             << "Registers:\n";

    for (std::size_t index = 0; index < 16; ++index) {
        m_output << "  R" << index << ": ";
        if (index < registers.size()) {
            m_output << registers[index];
        } else {
            m_output << "<missing>";
        }
        m_output << '\n';
    }
}

void Screen::displayMachineOutput(const std::string& text) const
{
    m_output << "\n=== Program Output ===\n";
    if (text.empty()) {
        m_output << "(no output)\n";
        return;
    }

    m_output << text;
    if (text[text.size() - 1] != '\n') {
        m_output << '\n';
    }
}

void Screen::showStatus(const std::string& message) const
{
    m_output << "Status: " << message << '\n';
}

void Screen::showError(const std::string& message) const
{
    m_output << "Error: " << message << '\n';
}
