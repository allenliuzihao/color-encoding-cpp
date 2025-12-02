#include "pch.h"

void parse_float(float input, uint32_t& sign, uint32_t& exponent, uint32_t& mantissa)
{
    uint32_t f_input = asuint(input);
    // sign bit
    bool isNegative = (f_input & 0x80000000) == 0x80000000;
    uint8_t parsed_exponent = ((0x7f800000 & f_input) >> 23) & 0x000000ff;
    uint32_t parsed_mantissa = f_input & (~0xff800000);

    sign = isNegative;
    exponent = parsed_exponent;
    mantissa = parsed_mantissa;
}

float compute_value(uint32_t sign, uint32_t exponent, uint32_t mantissa)
{
    float signValue = sign == 1 ? -1.f : 1.f;
    if (exponent == 0xff)
    {
        if (mantissa == 0)
        {
            return signValue * asfloat(0x7f800000);
        }
        else
        {
            return asfloat(0x7f800001);
        }
    }
    else if (exponent == 0)
    {
        float frac = std::ldexpf(float(mantissa), -23);
        float scale = std::ldexpf(1.f, -126);
        return signValue * frac * scale;
    }

    float frac = 1.0f + std::ldexpf(float(mantissa), -23);
    float scale = std::ldexpf(1.f, exponent - 127); // 2 ^ (exponent - 127)
    return signValue * frac * scale;
}