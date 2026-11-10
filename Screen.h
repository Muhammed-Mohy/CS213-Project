#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>

using namespace std;

class Screen {
public:
    Screen();

    void write(string value);
    string read() const;
    void display() const;
    void clear();

private:
    string content;
};

#endif