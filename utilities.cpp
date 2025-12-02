#include "pch.h"

uint32_t asuint(float x)
{
    return std::bit_cast<uint32_t>(x);
}

float asfloat(uint32_t x)
{
    return std::bit_cast<float>(x);
}

void print_binary(uint32_t input, uint32_t num_bits) 
{
    uint32_t curr = input;
    for (uint32_t i = 0; i < num_bits; ++i)
    {
        bool isOne = (curr & 0x80000000) == 0x80000000;
        std::cout << isOne;
        curr = curr << 1;
    }
    std::cout << std::endl;
}