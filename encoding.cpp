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

// computes f32tof16
void f32tof16(float input, uint16_t& sign, uint16_t& exponent, uint16_t& mantissa)
{
    uint32_t f_input = asuint(input) + 0x00001000;
    uint8_t parsed_exponent = ((0x7f800000 & f_input) >> 23) & 0x000000ff;
    uint32_t parsed_mantissa = f_input & (~0xff800000);

    // sign bit
    bool isNegative = (f_input & 0x80000000) > 0;
    sign = isNegative ? 1 : 0;

    // infinity and NaN case
    if (parsed_exponent == 0xff)
    {
        // infinity case
        if (mantissa == 0)
        {
            exponent = 0x1f;
            mantissa = 0;
            return;
        }
        else // NaN case
        {
            exponent = 0x1f;
            mantissa = 1; // set to some non-zero value
            return;
        }
    }
    else if (parsed_exponent == 0)
    {
        // f32 subnormal is too small to be represented in f16.
        exponent = 0;
        mantissa = 0;
        return;
    }

    // f32 normal case
    int32_t real_exponent = int32_t(parsed_exponent) - 127;
    int32_t f16_exponent = real_exponent + 15;
    uint16_t shifted_mantissa = (parsed_mantissa >> 13) & 0x3ff;

    if (f16_exponent >= 31)
    {
        // overflow to infinity
        exponent = 0x1f;
        mantissa = 0;
        return;
    }
    else if (f16_exponent <= 0)
    {
        uint32_t shifts = std::abs(real_exponent) - 14;
        exponent = 0;
        mantissa = (shifted_mantissa | 0x400) >> shifts;
        return;
    }

    exponent = f16_exponent & 0x1f; // the maximum is 31 and minimum is 0
    mantissa = shifted_mantissa; // take the top 10 bits
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

// computes f16tof32
float f16tof32(uint16_t sign, uint16_t exponent, uint16_t mantissa)
{
    float signValue = sign == 1 ? -1.f : 1.f;
    if (exponent == 0x1f)
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
        // f16 subnormal case
        uint32_t num_shifts = 0, curr = mantissa;
        while ((curr & 0x200) == 0)
        {
            num_shifts++;
            curr = curr << 1;
        }

        num_shifts++; // account for leading 1 bit
        // mantissa at the correct position
        uint32_t f32_mantissa = ((curr << 1) & 0x3ff) << 13;
        uint32_t f32_exponent = (127 - 14 - num_shifts) & 0xff;
        uint32_t f32 = (uint32_t(sign) << 31) | (f32_exponent << 23) | f32_mantissa;
        return asfloat(f32);
    }

    // start with normal case
    uint32_t f32_mantissa = uint32_t(mantissa) << 13; // put mantissa into place.
    uint32_t f32_exponent = (int32_t(exponent - 15) + 127) & 0xff;
    // put sign in place.
    uint32_t f32 = (uint32_t(sign) << 31) | (f32_exponent << 23) | f32_mantissa;
    return asfloat(f32);
}

float Float32::value() const
{
    return compute_value(sign, exponent, mantissa);
}

void Float32::print() const
{
    std::cout << "value: " << value() << std::endl;

    std::cout << "print as uint" << std::endl;
    std::cout << "sign: " << sign << std::endl;
    std::cout << "exponent: " << exponent << std::endl;
    std::cout << "mantissa: " << mantissa << std::endl;

    std::cout << "print as binary: " << std::endl;
    std::cout << "exponent: " << binary_string(exponent << 24, 8) << std::endl;
    std::cout << "mantissa: " << binary_string(mantissa << 9, 23) << std::endl;
    std::cout << std::endl;
}

Float32::Float32(float input)
{
    uint32_t local_sign = 0, local_exponent = 0, local_mantissa = 0;
    parse_float(input, local_sign, local_exponent, local_mantissa);
    this->sign = local_sign;
    this->exponent = local_exponent;
    this->mantissa = local_mantissa;
}

float Float16::value() const
{
    return f16tof32(sign, exponent, mantissa);
}

void Float16::print() const
{
    std::cout << "value: " << value() << std::endl;

    std::cout << "print as uint" << std::endl;
    std::cout << "sign: " << sign << std::endl;
    std::cout << "exponent: " << exponent << std::endl;
    std::cout << "mantissa: " << mantissa << std::endl;

    std::cout << "print as binary" << std::endl;
    std::cout << "exponent: " << binary_string(uint16_t(exponent << 11), 5) << std::endl;
    std::cout << "mantissa: " << binary_string(uint16_t(mantissa << 6), 10) << std::endl;
    std::cout << std::endl;
}

Float16::Float16(float input)
{
    uint16_t local_sign = 0, local_exponent = 0, local_mantissa = 0;
    f32tof16(input, local_sign, local_exponent, local_mantissa);
    this->sign = local_sign;
    this->exponent = local_exponent;
    this->mantissa = local_mantissa;
}

Float16::Float16(uint16_t raw)
{
    this->sign = (raw & 0x8000) >> 15;
    this->exponent = (raw & 0x7c00) >> 10;
    this->mantissa = raw & 0x03ff;
}