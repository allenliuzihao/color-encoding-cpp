#include "pch.h"

Float32 parse_float32(float input)
{
    uint32_t f_input = asuint(input);
    //print_binary(f_input);
    // sign bit
    bool isNegative = (f_input & 0x80000000) == 0x80000000;
    uint8_t exponent = ((0x7f800000 & f_input) >> 23) & 0x000000ff;
    uint32_t mantissa = f_input & (~0xff800000);

    return {
        .sign = isNegative,
        .exponent = exponent,
        .mantissa = mantissa
    };
}