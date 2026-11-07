#include "Screen.h"

#include <iomanip>
#include <sstream>

namespace {

std::string formatHexAddress(std::size_t address)
{
    std::ostringstream formattedAddress;
    formattedAddress << "0x"
                     << std::uppercase << std::hex
                     << std::setfill('0') << std::setw(2)
                     << address;
    return formattedAddress.str();
}

} // namespace

Screen::Screen(std::istream& input, std::ostream& output)
    : m_input(input),
      m_output(output),
      m_machineOutput()
{
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
    int choice = 0;

    if (!(choiceStream >> choice) || choice < 0) {
        return InvalidMenuChoice;
    }

    choiceStream >> std::ws;
    if (!choiceStream.eof()) {
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
        m_output << formatHexAddress(address) << ": "
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

void Screen::appendMachineOutput(const std::string& text)
{
    m_machineOutput += text;
}

void Screen::displayMachineOutput() const
{
    m_output << "\n=== Program Output ===\n";
    if (m_machineOutput.empty()) {
        m_output << "(no output)\n";
        return;
    }

    m_output << m_machineOutput;
    if (m_machineOutput[m_machineOutput.size() - 1] != '\n') {
        m_output << '\n';
    }
}

void Screen::clearMachineOutput()
{
    m_machineOutput.clear();
}

void Screen::showStatus(const std::string& message) const
{
    m_output << "Status: " << message << '\n';
}

void Screen::showError(const std::string& message) const
{
    m_output << "Error: " << message << '\n';
}
