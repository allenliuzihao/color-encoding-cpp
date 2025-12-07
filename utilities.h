#pragma once

struct float3
{
    float x;
    float y;
    float z;

    float3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct float4
{
    float x;
    float y;
    float z;
    float w;

    float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

uint32_t asuint(float x);
float asfloat(uint32_t x);

std::string binary_string(uint16_t input, uint16_t num_bits = 16);
std::string binary_string(uint32_t input, uint32_t num_bits = 32);

