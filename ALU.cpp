#include "ALU.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

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
    int n1 = stoi(a, nullptr, 16);
    int n2 = stoi(b, nullptr, 16);

    int s1 = (n1 >> 7) & 1;
    int e1 = (n1 >> 4) & 7;
    int m1 = n1 & 15;

    int s2 = (n2 >> 7) & 1;
    int e2 = (n2 >> 4) & 7;
    int m2 = n2 & 15;

    float v1 = (m1 / 16.0f) * pow(2.0f, e1 - 4);
    if (s1 == 1) v1 = -v1;

    float v2 = (m2 / 16.0f) * pow(2.0f, e2 - 4);
    if (s2 == 1) v2 = -v2;

    float sum = v1 + v2;

    if (sum == 0) return "00";

    int sign = 0;
    if (sum < 0) {
        sign = 1;
        sum = -sum;
    }

    int bestE = 0;
    int bestM = 0;
    float bestDiff = 1000000;

    for (int e = 0; e <= 7; e++) {
        float mFloat = sum / pow(2.0f, e - 4) * 16.0f;
        int m = (int)(mFloat + 0.5f);
        if (m >= 0 && m <= 15) {
            float back = (m / 16.0f) * pow(2.0f, e - 4);
            float diff = sum - back;
            if (diff < 0) diff = -diff;
            if (diff < bestDiff) {
                bestDiff = diff;
                bestE = e;
                bestM = m;
            }
        }
    }

    int result = (sign << 7) | (bestE << 4) | bestM;

    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << result;
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