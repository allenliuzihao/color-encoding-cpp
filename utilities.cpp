#include "pch.h"

void print_binary(uint32_t input) 
{
    uint32_t curr = input;
    for (int i = 0; i < 32; ++i)
    {
        bool isOne = (curr & 0x80000000) == 0x80000000;
        std::cout << isOne;
        curr = curr << 1;
    }
    std::cout << std::endl;
}