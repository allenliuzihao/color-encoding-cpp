#pragma once

// HDR formats
float4<Float16> encode_r16g16b16a16(float4<Float32> rgb);
float4<Float32> decode_r16g16b16a16(float4<Float16>);

uint32_t encode_r11g11b10(float3<Float32> rgb);
float3<Float32> decode_r11g11b10(uint32_t encoded);

uint32_t encode_r9g9b9e5(float3<Float32> rgb);
float3<Float32> decode_r9g9b9e5(uint32_t encoded);

// LDR format
uint32_t encode_rgb10a2_unorm(float4<Float32> rgba);
float4<Float32> decode_rgb10a2_unorm(uint32_t encoded);