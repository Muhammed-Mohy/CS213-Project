#include "Memory.h"
#include <iostream>
#include <fstream>

using namespace std;

Memory::Memory() {
    cells.resize(SIZE, "00");
}

bool Memory::isValidAddress(int address) {
    return address >= 0 && address < SIZE;
}

bool Memory::isEvenAddress(int address) {
    return address % 2 == 0;
}

bool Memory::isValidInstructionAddress(int address) {
    return isValidAddress(address) && isEvenAddress(address);
}

string Memory::read(int address) {
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

string Memory::readWord(int address) {
    if (isValidInstructionAddress(address)) {
        return cells[address] + cells[address + 1];
    } else {
        cout << "Error: Invalid instruction address " << address << endl;
        return "00";
    }
}

void Memory::loadFromFile(string filePath, int startAddress) {
    if (!isValidAddress(startAddress)) {
        cout << "Error: Invalid start address for loading file."<< endl;
        return;
    }
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    int address = startAddress;
    while (file >> line && address < SCREEN_ADDR) {
        cells[address] = line;
        address++;
    }

    file.close();
}

void Memory::displayMatrix() {
    for (int i = 0; i < SIZE; i++) {
        if (i == SCREEN_ADDR) {
            cout << "[FF: Screen I/O]" << endl;
        } else {
            cout <<  cells[i] << " " << endl;
        }
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
}

void Memory::clear() {
    for (int i = 0; i < SIZE; i++) {
        cells[i] = "00";
    }
    screen.clear();
}





















































