#include "Memory.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

Memory::Memory(Screen& screen) : screen(screen) {
    cells.resize(SIZE, "00");
}

bool Memory::isValidAddress(int address) const {
    return address >= 0 && address < SIZE;
}

bool Memory::isEvenAddress(int address) const {
    return address % 2 == 0;
}

bool Memory::isValidInstructionAddress(int address) const {
    return isValidAddress(address) && isEvenAddress(address) && (address + 1 < SCREEN_ADDR);
}

string Memory::read(int address) const {
    if (address == SCREEN_ADDR) {
        return screen.read();
    }
    if (isValidAddress(address)) {
        return cells[address];
    } else {
        cout << "Error: Invalid memory address " << address << endl;
        return "00";
    }
}

void Memory::write(int address, string value) {
    if (address == SCREEN_ADDR) {
        screen.write(value);
    } else if (isValidAddress(address)) {
        cells[address] = value;
    } else {
        cout << "Error: Invalid memory address " << address << endl;
    }
}

string Memory::readWord(int address) const {
    if (!isValidInstructionAddress(address)) {
        cout << "Error: Invalid instruction address "
             << address << endl;
        return "";
    }

    return cells[address] + cells[address + 1];
}

void Memory::loadFromFile(string filePath, int startAddress) {
    if (!isValidInstructionAddress(startAddress)) {
        cout << "Error: Invalid start address for loading file."
             << endl;
        return;
    }

    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "Error: Could not open file "
             << filePath << endl;
        return;
    }

    string line;
    int address = startAddress;

    while (file >> line) {
        if (address >= SCREEN_ADDR) {
            cout << "Error: Program exceeds available memory."
                 << endl;
            break;
        }

        if (line.length() != 2 ||
            !isxdigit(static_cast<unsigned char>(line[0])) ||
            !isxdigit(static_cast<unsigned char>(line[1]))) {
            cout << "Error: Invalid memory cell value: "
                 << line << endl;
            break;
        }

        cells[address] = line;
        address++;
    }

    file.close();
}

void Memory::displayMatrix() const {
    for (int i = 0; i < SIZE; i++) {
        if (i == SCREEN_ADDR) {
            cout << "[FF: Screen I/O]" << endl;
        } else {
            cout << cells[i] << " ";
            if ((i + 1) % 16 == 0) {
                cout << endl;
            }
        }
    }
}

void Memory::clear() {
    for (int i = 0; i < SIZE; i++) {
        cells[i] = "00";
    }
    screen.clear();
}