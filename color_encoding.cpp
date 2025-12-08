#include "pch.h"

uint32_t encode_rgb10a2_unorm(float4<Float32> rgba)
{
    rgba = saturate(rgba);

    uint32_t r = static_cast<uint32_t>(rgba.x() * 1023.0f + 0.5f);
    uint32_t g = static_cast<uint32_t>(rgba.y() * 1023.0f + 0.5f);
    uint32_t b = static_cast<uint32_t>(rgba.z() * 1023.0f + 0.5f);
    uint32_t a = static_cast<uint32_t>(rgba.w() * 3.0f + 0.5f);

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
    rgb = max(rgb, 0.0f);

    uint16_t r16 = Float16((float)rgb.x()).raw() + 0x0008;
    uint16_t g16 = Float16((float)rgb.y()).raw() + 0x0008;
    uint16_t b16 = Float16((float)rgb.z()).raw() + 0x0010;

    uint32_t result = 0;
    // r: 5 bits exponent, 6 bits mantissa
    uint32_t r = uint32_t(r16 & 0x7ff0) >> 4;
    // g: 5 bits exponent, 6 bits mantissa
    uint32_t g = uint32_t(g16 & 0x7ff0) << 7;
    // b: 5 bits exponent, 5 bits mantissa
    uint32_t b = uint32_t(b16 & 0x7fe0) << 17;
    return r | g | b;
}

float3<Float32> decode_r11g11b10(uint32_t encoded)
{
    uint16_t r16 = uint16_t((encoded & 0x000007ff) << 4);
    uint16_t g16 = uint16_t((encoded & 0x003ff800) >> 7);
    uint16_t b16 = uint16_t((encoded & 0xffc00000) >> 17);

    Float16 r_f16 = Float16(r16);
    Float16 g_f16 = Float16(g16);
    Float16 b_f16 = Float16(b16);

    return float3<Float32>{
        r_f16.value(),
        g_f16.value(),
        b_f16.value()
    };
}

uint32_t encode_r9g9b9e5(float3<Float32> rgb)
{

    return 0;
}

float3<Float32> decode_r9g9b9e5(uint32_t encoded)
{
    return float3<Float32>{
    };
}

float4<Float16> encode_r16g16b16a16(float4<Float32> rgb)
{
    float4<Float16> result = {
        Float16((float)rgb.x()),
        Float16((float)rgb.y()),
        Float16((float)rgb.z()),
        Float16((float)rgb.w())
    };
    return result;
}

float4<Float32> decode_r16g16b16a16(float4<Float16> rgb)
{
    float4 <Float32> result = {
        Float32((float)rgb.x()),
        Float32((float)rgb.y()),
        Float32((float)rgb.z()),
        Float32((float)rgb.w())
    };
    return result;
}