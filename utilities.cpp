#include "pch.h"

void print_binary(uint32_t input) 
{
    uint32_t curr = input;
    while (curr != 0) 
    {
        bool isOne = (curr & 0x1) == 0x1;
        std::cout << isOne;
        curr = curr >> 1;
    }
    std::cout << std::endl;
}