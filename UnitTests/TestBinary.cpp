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
            Assert::AreEqual("1000000000000000", str3.c_str());

            auto str4 = binary_string(uint16_t(0xf010));
            Assert::AreEqual("1111000000010000", str4.c_str());

            auto str5 = binary_string(uint16_t(0xfffa));
            Assert::AreEqual("1111111111111010", str5.c_str());

            auto str1 = binary_string(uint16_t(0xfffa), 14);
            Assert::AreEqual( "11111111111110", str1.c_str());

            auto str2 = binary_string(uint16_t(0x1000), 4);
            Assert::AreEqual("0001", str2.c_str());
        }

        TEST_METHOD(FP32Binary)
        {
            auto str1 = binary_string(uint32_t(0x00000000));
            Assert::AreEqual("00000000000000000000000000000000", str1.c_str());

            auto str2 = binary_string(uint32_t(0x07804000));
            Assert::AreEqual("00000111100000000100000000000000", str2.c_str());

            auto str3 = binary_string(uint32_t(0x7F800000));
            Assert::AreEqual("01111111100000000000000000000000", str3.c_str());

            auto str4 = binary_string(uint32_t(0x7F800000), 4);
            Assert::AreEqual("0111", str4.c_str());

            auto str5 = binary_string(uint32_t(0x07804000), 18);
            Assert::AreEqual("000001111000000001", str5.c_str());

        }
    };
}
