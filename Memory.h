#pragma once
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
    string read(int address);
    void write(int address, string value);
    string readWord(int address);
    void loadFromFile(string filePath, int startAddress);

    bool isValidAddress(int address);
    bool isEvenAddress(int address);
    bool isValidInstructionAddress(int address);

    void displayMatrix();
    void clear();

    Memory(Screen& screen);
#endif 