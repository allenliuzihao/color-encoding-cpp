#pragma once

void parse_float(float input, uint32_t& sign, uint32_t& exponent, uint32_t& mantissa);
float compute_value(uint32_t sign, uint32_t exponent, uint32_t mantissa);

void f32tof16(float input, uint16_t& sign, uint16_t& exponent, uint16_t& mantissa);
float f16tof32(uint16_t sign, uint16_t exponent, uint16_t mantissa);

struct Float32
{
    uint32_t sign : 1;
    uint32_t exponent : 8;
    uint32_t mantissa : 23;

    float value() const;
    void print() const;
    Float32(float input);
};

struct Float16
{
    uint16_t sign : 1;
    uint16_t exponent : 5;
    uint16_t mantissa : 10;

    float value() const;
    void print() const;
    Float16(float input);
    Float16(uint16_t raw);
};

