#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(TestBinaryConversion)
    {
    public:
        TEST_METHOD(FP16Binary)
        {
            auto str3 = binary_string(uint16_t(0x8000));
            Assert::AreEqual(str3.c_str(), "1000000000000000");

            auto str4 = binary_string(uint16_t(0xf010));
            Assert::AreEqual(str4.c_str(), "1111000000010000");

            auto str5 = binary_string(uint16_t(0xfffa));
            Assert::AreEqual(str5.c_str(), "1111111111111010");
        }

        TEST_METHOD(FP32Binary)
        {
            auto str1 = binary_string(uint32_t(0x00000000));
            Assert::AreEqual(str1.c_str(), "00000000000000000000000000000000");

            auto str2 = binary_string(uint32_t(0x07804000));
            Assert::AreEqual(str2.c_str(), "00000111100000000100000000000000");

            auto str3 = binary_string(uint32_t(0x7F800000));
            Assert::AreEqual(str3.c_str(), "01111111100000000000000000000000");
        }
    };
}
