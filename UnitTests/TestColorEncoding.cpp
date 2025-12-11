#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(TestColorEncoding)
    {
    public:
        TEST_METHOD(TestR16G16B16A16)
        {
            float4<Float32> expected = { 1.0f, 0.5f, 0.25f, 0.75f };
            float4<Float32> decoded = decode_r16g16b16a16(encode_r16g16b16a16(expected));
            Assert::IsTrue(expected == decoded);

            float4<Float32> input = { 0.33f, 0.5f, 0.332f, 123.321f };
            decoded = decode_r16g16b16a16(encode_r16g16b16a16(input));
            expected = { 0.330078125f, 0.5f, 0.33203125f, 123.3125f };
            Assert::IsTrue(expected == decoded);

            // Edge cases: min and max float16 values
            input = { 0.0f, 65504.0f, -65504.0f, 1.0f };
            decoded = decode_r16g16b16a16(encode_r16g16b16a16(input));
            expected = { 0.0f, 65504.0f, -65504.0f, 1.0f };
            Assert::IsTrue(expected == decoded);

            // Smallest positive normal float16
            input = { 6.103515625e-05, 1.0f, 0.0f, -1.0f };
            decoded = decode_r16g16b16a16(encode_r16g16b16a16(input));
            float x = decoded.x();
            float y = decoded.y();
            float z = decoded.z();
            expected = { 6.103515625e-05, 1.0f, 0.0f, -1.0f };
            Assert::IsTrue(expected == decoded);

            // Subnormal value (will be rounded to zero in float16)
            input = { 1e-08f, 0.0f, 0.0f, 0.0f };
            decoded = decode_r16g16b16a16(encode_r16g16b16a16(input));
            expected = { 0.0f, 0.0f, 0.0f, 0.0f };
            Assert::IsTrue(expected == decoded);

            // Negative values
            input = { -0.5f, -1.0f, -0.25f, -65504.0f };
            decoded = decode_r16g16b16a16(encode_r16g16b16a16(input));
            expected = { -0.5f, -1.0f, -0.25f, -65504.0f };
            Assert::IsTrue(expected == decoded);
        }

        TEST_METHOD(TestR11G11B10)
        {
            float3<Float32> input = { 0.0f, 0.0f, 0.0f };
            float3<Float32> expected = { 1.0f, 0.5f, 0.25f };
            float3<Float32> decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(expected == decoded);

            expected = { 1.0f, 1.0f, 1.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(expected == decoded);

            expected = { 0.0f, 0.0f, 0.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(expected == decoded);

            expected = { 0.5f, 0.5f, 0.5f };
            decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(expected == decoded);

            expected = { 65504.0f, 65504.0f, 65504.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(std::isinf(decoded.x()) && std::isinf(decoded.y()) && std::isinf(decoded.z()));

            expected = { 1e-5f, 2e-5f, 3e-5f };
            decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(approxEqual(expected, decoded, 1e-5));

            input = { 10.32f, 0.001f, 23.f };
            expected = { 10.375f, 0.001f, 23.f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(expected, decoded));

            input = { 0.33f, 0.66f, 0.99f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-2));

            input = { 4.32f, 6.1f, 0.11f };
            expected = { 4.3125f, 6.125f, 0.109375f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(decoded == expected);

            input = { -1.0f, 2.0f, 0.5f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            expected = { 0.0f, 2.0f, 0.5f };
            Assert::IsTrue(decoded == expected);

            // Channel-specific edge cases
            input = { 1.0f, 0.0f, 0.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            expected = { 1.0f, 0.0f, 0.0f };
            Assert::IsTrue(decoded == expected);

            input = { 0.0f, 1.0f, 0.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            expected = { 0.0f, 1.0f, 0.0f };
            Assert::IsTrue(decoded == expected);

            input = { 0.0f, 0.0f, 1.0f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            expected = { 0.0f, 0.0f, 1.0f };
            Assert::IsTrue(decoded == expected);

            // Test with values just below and above quantization thresholds
            input = { 0.499f, 0.501f, 0.249f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-2));

            input = { 0.999f, 0.001f, 0.751f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-3));

            input = { 77.23f, 98.88f, 502.2f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            expected = { 77.0f, 99.0f, 504.0f };
            Assert::IsTrue(decoded == expected);
        }

        TEST_METHOD(TestR10G10B10A2)
        {
            // Basic round-trip test
            float4<Float32> input = { 1.0f, 0.5f, 0.25f, 1.0f };
            float4<Float32> decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            // Test with minimum values
            input = { 0.0f, 0.0f, 0.0f, 0.0f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            // Test with mid-range values
            input = { 0.5f, 0.5f, 0.5f, 0.5f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            // Test with values that are not exactly representable
            input = { 0.33f, 0.66f, 0.99f, 0.25f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            // The expected values are the nearest representable values in 10/2 bit UNORM
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            input = { 0.33f, 0.26f, 0.99f, 0.1f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            // The expected values are the nearest representable values in 10/2 bit UNORM
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            input = { 0.23f, 0.66f, 0.99f, 0.33f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            // The expected values are the nearest representable values in 10/2 bit UNORM
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            input = { 0.23f, 0.66f, 0.99f, 0.78f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            // The expected values are the nearest representable values in 10/2 bit UNORM
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            input = { 0.23f, 0.66f, 0.99f, 0.83f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            // The expected values are the nearest representable values in 10/2 bit UNORM
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);

            // Test with out-of-range values (should be clamped)
            input = { -1.0f, 2.0f, 0.5f, 5.0f };
            decoded = decode_rgb10a2_unorm(encode_rgb10a2_unorm(input));
            Assert::IsTrue(GetExpectedR10G10B10A2(input) == decoded);
        }

        TEST_METHOD(TestR9G9B9E5)
        {
            float3<Float32> input = { 1.0f, 0.5f, 0.25f };
            float3<Float32> decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(input == decoded);

            // check denormals and small values are rounded to zero
            input = { 1e-8f, 0.0f, 0.0f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            float x = decoded.x();
            float y = decoded.y();
            float z = decoded.z();
            Assert::IsTrue(decoded == float3<Float32>{ 0.0f, 0.0f, 0.0f });
        }
    private:
        float4<Float32> GetExpectedR10G10B10A2(float4<Float32> rgba)
        {
            rgba = saturate(rgba);

            return float4<Float32>{
                std::round(rgba.x() * 1023.0f) / 1023.0f,
                std::round(rgba.y() * 1023.0f) / 1023.0f,
                std::round(rgba.z() * 1023.0f) / 1023.0f,
                std::round(rgba.w() * 3.0f) / 3.0f
            };
        }
    };
}
