#pragma once

template<typename T>
struct float3
{
    T x;
    T y;
    T z;

    float3() : x(0), y(0), z(0) {}
    float3(T x, T y, T z) : x(x), y(y), z(z) {}
};

template<typename T>
struct float4
{
    T x;
    T y;
    T z;
    T w;

    float4() : x(0), y(0), z(0), w(0) {}
    float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

template<typename T>
float3<T> saturate(float3<T> v)
{
    float3<T> result = {};
    result.x = std::clamp((float) v.x, 0.f, 1.f);
    result.y = std::clamp((float) v.y, 0.f, 1.f);
    result.z = std::clamp((float) v.z, 0.f, 1.f);
    return result;
}

template<typename T>
float4<T> saturate(float4<T> v)
{
    float4<T> result = {};
    result.x = std::clamp((float) v.x, 0.f, 1.f);
    result.y = std::clamp((float) v.y, 0.f, 1.f);
    result.z = std::clamp((float) v.z, 0.f, 1.f);
    result.w = std::clamp((float) v.w, 0.f, 1.f);
    return result;
}

template<typename T>
float3<T> min(float3<T> v, float minValue)
{
    float3<T> result = {};
    result.x = std::min((float)v.x, minValue);
    result.y = std::min((float)v.y, minValue);
    result.z = std::min((float)v.z, minValue);
    return result;
}

template<typename T>
float4<T> min(float4<T> v, float minValue)
{
    float4<T> result = {};
    result.x = std::min((float)v.x, minValue);
    result.y = std::min((float)v.y, minValue);
    result.z = std::min((float)v.z, minValue);
    result.w = std::min((float)v.w, minValue);
    return result;
}

template<typename T>
float3<T> max(float3<T> v, float maxValue)
{
    float3<T> result = {};
    result.x = std::max((float)v.x, maxValue);
    result.y = std::max((float)v.y, maxValue);
    result.z = std::max((float)v.z, maxValue);
    return result;
}

template<typename T>
float4<T> max(float4<T> v, float maxValue)
{
    float4<T> result = {};
    result.x = std::max((float)v.x, maxValue);
    result.y = std::max((float)v.y, maxValue);
    result.z = std::max((float)v.z, maxValue);
    result.w = std::max((float)v.w, maxValue);
    return result;
}

uint32_t asuint(float x);
float asfloat(uint32_t x);

std::string binary_string(uint16_t input, uint16_t num_bits = 16);
std::string binary_string(uint32_t input, uint32_t num_bits = 32);

