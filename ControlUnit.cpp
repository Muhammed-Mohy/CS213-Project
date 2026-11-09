#include "ControlUnit.h"

Instruction ControlUnit::parse(const std::string& rawIR)
{
    return Instruction(rawIR);
}

bool ControlUnit::validate(const Instruction& inst)
{
    std::string raw{ inst.getRaw() };

    if (raw.length() != 4)
        return false;

    for (char c : raw)
    {
        bool isHex = (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');

        if (!isHex)
            return false;
    }

    char op{ inst.getOpcode() };
    if (op >= 'a' && op <= 'z')
    {
        op = static_cast<char>(op - 32);
    }

    int r{ inst.getR() };
    int s{ inst.getS() };
    int t{ inst.getT() };
    int address{ inst.getAddressXY() };

    switch (op)
    {
        case '1':
        case '2':
        case '3':
            return r >= 0 && r <= 15 &&
                   address >= 0 && address <= 0xFF;

        case '4':
            return r == 0 &&
                   s >= 0 && s <= 15 &&
                   t >= 0 && t <= 15;

        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return r >= 0 && r <= 15 &&
                   s >= 0 && s <= 15 &&
                   t >= 0 && t <= 15;

        case 'A':
            return r >= 0 && r <= 15 &&
                   s == 0 &&
                   t >= 0 && t <= 15;

        case 'B':
            return r >= 0 && r <= 15 &&
                   address % 2 == 0 &&
                   address + 1 < 0xFF;

        case 'C':
            return raw == "C000" || raw == "c000";

        default:
            return false;
    }
}