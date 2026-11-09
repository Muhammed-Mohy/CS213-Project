#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <string>

using namespace std;

class ALU
{
public:

    string addTwoComplement(string a, string b);
    string addFloatingPoint(string a, string b);
    string bitwiseOr(string a, string b);
    string bitwiseAnd(string a, string b);
    string bitwiseXor(string a, string b);
    string rotateRight(string value,int times);

};

#endif // ALU_H