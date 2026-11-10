#include "Screen.h"
#include <iostream>

using namespace std;

Screen::Screen() {
    content = "";
}

void Screen::write(string value) {
    content = value;
}

string Screen::read() const {
    return content;
}

void Screen::display() const {
    cout << content << endl;
}

void Screen::clear() {
    content = "";
}
