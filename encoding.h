#pragma once

struct Float32
{
    uint32_t sign : 1;
    uint32_t exponent : 8;
    uint32_t mantissa : 23;

    float value() const
    {
        float signValue = sign == 1 ? -1.f : 1.f;
        float m = 1.0f + std::ldexpf(float(mantissa), -23);
        float scale = std::ldexpf(2.f, exponent - 127);
        float frac = signValue * m * scale;
        return frac;
    }

    void print() const 
    {
        std::cout << "sign: " << sign << std::endl;
        std::cout << "exponent: " << exponent << std::endl;
        std::cout << "mantissa: " << mantissa << std::endl;
    }
};

Float32 parse_float32(float input);
