#include "ALU.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

string ALU::addTwoComplement(string a,string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);
    
    int result = num1 + num2;
    result &= 0xFF;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;

    return ss.str();
}

string ALU::addFloatingPoint(string a, string b)
{
   float F1 = stoi(a, nullptr, 16);
   float F2 = stoi(b, nullptr, 16);

   float result = F1 + F2;

   int intResult = static_cast<int>(result) & 0xFF;

   stringstream ss;
   ss << uppercase << hex << setw(2) << setfill('0') << intResult;

   return ss.str();
}

string ALU::bitwiseOr(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = (num1 | num2) & 0xFF;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;

    return ss.str();
}

string ALU::bitwiseAnd(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = (num1 & num2) & 0xFF;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;

    return ss.str();
}  

string ALU::bitwiseXor(string a, string b)
{
    int num1 = stoi(a, nullptr, 16);
    int num2 = stoi(b, nullptr, 16);

    int result = (num1 ^ num2) & 0xFF;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;

    return ss.str();
}

string ALU::rotateRight(string value, int times)
{
    int num = stoi(value, nullptr, 16);
    int bitSize = 8;

    times %= bitSize;
    int result = ((num >> times) | (num << (bitSize - times))) & 0xFF;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;

    return ss.str();

}