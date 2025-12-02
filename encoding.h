#pragma once

void parse_float(float input, uint32_t& sign, uint32_t& exponent, uint32_t& mantissa);
float compute_value(uint32_t sign, uint32_t exponent, uint32_t mantissa);

struct Float32
{
    uint32_t sign : 1;
    uint32_t exponent : 8;
    uint32_t mantissa : 23;

    float value() const
    {
        return compute_value(sign, exponent, mantissa);
    }

    void print() const 
    {
        std::cout << "value: " << value() << std::endl;

        std::cout << "print as uint" << std::endl;
        std::cout << "sign: " << sign << std::endl;
        std::cout << "exponent: " << exponent << std::endl;
        std::cout << "mantissa: " << mantissa << std::endl;

        std::cout << "print as binary" << std::endl;
        print_binary(exponent << 24, 8);
        print_binary(mantissa << 9, 23);
        std::cout << std::endl;
    }

    Float32(float input)
    {
        uint32_t sign, exponent, mantissa;
        parse_float(input, sign, exponent, mantissa);
        this->sign = sign;
        this->exponent = exponent;
        this->mantissa = mantissa;
    }
};

