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
            Assert::IsTrue(approxEqual(expected, decoded, 1e-5f));

            input = { 10.32f, 0.001f, 23.f };
            expected = { 10.375f, 0.001f, 23.f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(expected, decoded));

            input = { 0.33f, 0.66f, 0.99f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-2f));

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
            Assert::IsTrue(approxEqual(input, decoded, 1e-2f));

            input = { 0.999f, 0.001f, 0.751f };
            decoded = decode_r11g11b10(encode_r11g11b10(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-3f));

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
            Assert::IsTrue(decoded == float3<Float32>{ 0.0f, 0.0f, 0.0f });

            input = { 0.1f, 0.2f, 0.3f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-3f));

            input = { 10.0f, 20.0f, 30.0f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(input == decoded);

            input = { 1e-8f, 10.31f, 41.2f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(float3<Float32>{ 0.0f, 10.31f, 41.2f }, decoded, 1e-1f));

            input = { 0.33f, 0.66f, 0.99f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-2f));

            input = { 77.23f, 98.88f, 502.2f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e1));

            // maximum representable value of R9G9B9E5
            input = { 57344.0f, 57344.0f, 57344.0f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(input == decoded);

            // values exceeding maximum representable value should be clamped
            input = { 60000.0f, 70000.0f, 80000.0f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(decoded == float3<Float32>{ 60032.0f, 65408.f, 65408.f });

            // a mix of really large and really small values
            input = { 1e-8f, 1e4f, 1e8f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(float3<Float32>{ 0.0f, 9984.f, 65408.f } == decoded);

            // all small values
            input = { 1e-5f, 2e-5f, 3e-5f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(float3<Float32>{ 0.0f, 0.0f, 0.0f }, decoded));

            // small values representable in R9G9B9E5
            input = { 0.0009765625f, 0.001953125f, 0.00390625f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(input, decoded, 1e-6f));

            input = { -1.0f, 2.0f, 0.5f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(approxEqual(float3<Float32>{ 0.0f, 2.0f, 0.5f }, decoded, 1e-6f));

            // smallest values representable in R9G9B9E5
            float minValue = ldexpf(1.0, -24);
            input = { minValue, minValue, minValue };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(input == decoded);

            // values just below smallest representable in R9G9B9E5 should round to zero
            input = { minValue * 0.9f, minValue * 0.9f, minValue * 0.9f };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(float3<Float32>{ 0.0f, 0.0f, 0.0f } == decoded);

            // exhaustive test for all representable mantissa values with exponent -24
            // this covers all smallest representable values in R9G9B9E5
            for (uint16_t value = 0; value < 512; ++value)
            {
                float val = ldexpf(value, -24);
                input = { val, val, val };
                decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
                float x = decoded.x();
                float y = decoded.y();
                float z = decoded.z();
                Assert::IsTrue(input == decoded);
            }

            // exhaustive test for a range of exponents and mantissas
            // these cover all representable values in R9G9B9E5
            for (int16_t exp = -14; exp <= 16; ++exp)
            {
                for (uint16_t mantissa = 0; mantissa < 512; ++mantissa) // step to reduce test time
                {
                    float val = ldexpf(static_cast<float>(mantissa), exp - 9);
                    input = { val, val, val };
                    decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
                    Assert::IsTrue(input == decoded);
                }
            }

            // finally check rounding behavior for values between representable values
            float no_rounding = asfloat(0x3fff8000);
            input = { no_rounding, no_rounding, no_rounding };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            Assert::IsTrue(input == decoded);

            float rounding_up = asfloat(0x3fffc000);
            input = { rounding_up, rounding_up, rounding_up };
            decoded = decode_r9g9b9e5(encode_r9g9b9e5(input));
            float x = decoded.x();
            float y = decoded.y();
            float z = decoded.z();
            Assert::IsTrue(decoded == float3<Float32>{ 2.0f, 2.0f, 2.0f });
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
