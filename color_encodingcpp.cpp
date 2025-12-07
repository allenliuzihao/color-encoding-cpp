#include "pch.h"

uint32_t encode_rgb10a2_unorm(float4<Float32> rgba)
{
    rgba = saturate(rgba);

    uint32_t r = static_cast<uint32_t>(rgba.x * 1023.0f + 0.5f);
    uint32_t g = static_cast<uint32_t>(rgba.y * 1023.0f + 0.5f);
    uint32_t b = static_cast<uint32_t>(rgba.z * 1023.0f + 0.5f);
    uint32_t a = static_cast<uint32_t>(rgba.w * 3.0f + 0.5f);

    return r | (g << 10) | (b << 20) | (a << 30);
}

float4<Float32> decode_rgb10a2_unorm(uint32_t encoded)
{
    uint32_t r = (encoded & 0x000003FF);
    uint32_t g = (encoded & 0x000FFC00) >> 10;
    uint32_t b = (encoded & 0x3FF00000) >> 20;
    uint32_t a = (encoded & 0xC0000000) >> 30;
    float4<Float32> result = {
        r / 1023.0f,
        g / 1023.0f,
        b / 1023.0f,
        a / 3.0f
    };
    return result;
}

uint32_t encode_r11g11b10(float3<Float32> rgb)
{
    return 0;
}

float3<Float32> decode_r11g11b10(uint32_t encoded)
{
    return float3<Float32>{};
}

uint32_t encode_r9g9b9e5(float3<Float32> rgb)
{
    return 0;
}

float3<Float32> decode_r9g9b9e5(uint32_t encoded)
{
    return float3<Float32>{};
}