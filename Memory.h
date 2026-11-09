#ifndef MEMORY_H
#define MEMORY_H
#include "Screen.h"

#include <string>
#include <vector>

using namespace std;

class Memory
{
private:
    static const int SIZE = 256;
    static const int SCREEN_ADDR = 0xFF;
    vector<string>cells;
    Screen& screen;
public:
    string read(int address) const;
    void write(int address, string value);
    string readWord(int address) const;
    void loadFromFile(string filePath, int startAddress);

    bool isValidAddress(int address) const;
    bool isEvenAddress(int address) const;
    bool isValidInstructionAddress(int address) const;

    void displayMatrix() const;
    void clear();

    Memory(Screen& screen);
};    
#endif 