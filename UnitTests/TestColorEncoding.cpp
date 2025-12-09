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
        }

        TEST_METHOD(TestR11G11B10)
        {
            
        }

        TEST_METHOD(TestR10G10B10A2)
        {

        }

        TEST_METHOD(TestR9G9B9E5)
        {

        }
    };
}
