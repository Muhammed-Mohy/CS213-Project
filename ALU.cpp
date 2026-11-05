#include "ALU.h"
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

string ALU::addTwoComplement(string a,string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);
    
    int result = num1 + num2;
    
    stringstream ss;
    ss << hex << result;

    return ss.str();
}

string ALU::addFloatingPoint(string a, string b)
{
   float F1 = stof(a);
   float F2 = stof(b);

   float result = F1 + F2;

   return to_string(result);
}

string ALU::bitwiseOr(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = num1 | num2;

    stringstream ss;
    ss << hex << result;
    
    return ss.str();
}

string ALU::bitwiseAnd(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = num1 & num2;

    stringstream ss;
    ss << hex << result;

    return ss.str();
}  

string ALU::bitwiseXor(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = num1 ^ num2;

    stringstream ss;
    ss << hex << result;

    return ss.str();
}

string ALU::rotateRight(string value, int times)
{
    int num = stoi(value, nullptr, 16);
    int bitSize = sizeof(num) * 8;

    times = times % bitSize;
    int result = (num >> times) | (num << (bitSize - times));

    stringstream ss;
    ss << hex << result;

    return ss.str();

}

ALU::ALU()
{
}

ALU::~ALU()
{
}
