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
            float3<Float32> expected = { 1.0f, 0.5f, 0.25f };
            float3<Float32> decoded = decode_r11g11b10(encode_r11g11b10(expected));
            Assert::IsTrue(expected == decoded);

            // Test with a range of values, including edge cases
            struct TestCase
            {
                float r, g, b;
            } testCases[] = {
                {1.0f, 1.0f, 1.0f},         // max
                {0.0f, 0.0f, 0.0f},         // min
                {0.5f, 0.5f, 0.5f},         // mid
                {0.33f, 0.5f, 0.332f},      // arbitrary
                {65504.0f, 65504.0f, 65504.0f}, // largest float16
                {1e-5f, 2e-5f, 3e-5f},      // small values
            };

            for (const auto& tc : testCases)
            {
                float3<Float32> input = { tc.r, tc.g, tc.b };
                uint32_t encoded = encode_r11g11b10(input);
                float3<Float32> decoded = decode_r11g11b10(encoded);

                float x = decoded.x();
                float y = decoded.y();
                float z = decoded.z();

                // Allow a small epsilon due to quantization
                float epsilon = 1e-3f; // R/G: 11 bits, B: 10 bits
                //Assert::IsTrue(std::abs(input.x() - decoded.x()) <= epsilon);
                //Assert::IsTrue(std::abs(input.y() - decoded.y()) <= epsilon);
                //Assert::IsTrue(std::abs(input.z() - decoded.z()) <= epsilon);
            }
        }

        TEST_METHOD(TestR10G10B10A2)
        {

        }

        TEST_METHOD(TestR9G9B9E5)
        {

        }
    };
}
