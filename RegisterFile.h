#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <string>
#include <vector>

class RegisterFile {
private:
    static const int COUNT = 16; 
    std::vector<std::string> regs;

public:
    RegisterFile();

    std::string read(int index) const; 
    void write(int index, const std::string& value); 
    void reset();
    void display() const; 
};

#endif