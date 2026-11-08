#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <string>
#include <vector>

class RegisterFile {
private:
    std::vector<std::string> registers;

public:
    RegisterFile();

    void setRegister(int index, const std::string& value);
    std::string getRegister(int index) const;
    void reset();
};

#endif