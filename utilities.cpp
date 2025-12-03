#include "pch.h"

uint32_t asuint(float x)
{
    return std::bit_cast<uint32_t>(x);
}

float asfloat(uint32_t x)
{
    return std::bit_cast<float>(x);
}

std::string binary_string(uint16_t input, uint16_t num_bits)
{
    std::string result{};

    uint16_t curr = input;
    for (uint16_t i = 0; i < num_bits; ++i)
    {
        bool isOne = (curr & 0x8000) == 0x8000;
        result.push_back(isOne ? '1' : '0');
        curr = curr << 1;
    }
    return result;
}

std::string binary_string(uint32_t input, uint32_t num_bits)
{
    std::string result{};

    uint32_t curr = input;
    for (uint32_t i = 0; i < num_bits; ++i)
    {
        bool isOne = (curr & 0x80000000) == 0x80000000;
        result.push_back(isOne ? '1' : '0');
        curr = curr << 1;
    }
    return result;
}