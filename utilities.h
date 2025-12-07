#pragma once

struct float3
{
    float x;
    float y;
    float z;

    float3() : x(0), y(0), z(0) {}
    float3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct float4
{
    float x;
    float y;
    float z;
    float w;

    float4() : x(0), y(0), z(0), w(0) {}
    float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

uint32_t asuint(float x);
float asfloat(uint32_t x);

float3 saturate(float3 v);
float4 saturate(float4 v);

std::string binary_string(uint16_t input, uint16_t num_bits = 16);
std::string binary_string(uint32_t input, uint32_t num_bits = 32);

