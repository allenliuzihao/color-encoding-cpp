#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(TestFP16)
    {
    public:
        TEST_METHOD(FP16Specials)
        {
            /* testing special numbers */
            auto parsedFloat = Float16(float(65505));
            auto value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && value == 65504);

            parsedFloat = Float16(float(-65505));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && value == -65504);

            parsedFloat = Float16(float(65520));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0 && std::isinf(value));
            
            parsedFloat = Float16(float(65521));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0 && std::isinf(value));
            
            parsedFloat = Float16(float(-65521));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0 && std::isinf(value) && value < 0);
            
            parsedFloat = Float16(float(125521));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0 && std::isinf(value) && value > 0);

            parsedFloat = Float16(asfloat(0x7f800001));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0x3ff && std::isnan(value));
        
            parsedFloat = Float16(asfloat(0x477FF000));
            value = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0 && std::isinf(value) && value > 0);
        }

        TEST_METHOD(FP16Normals)
        {
            /* testing normal numbers */
            // test maximum float16 value
            auto parsedFloat = Float16(float(65504));
            float val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && val == 65504.0f);

            parsedFloat = Float16(float(-65504));
            parsedFloat.print();
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && val == -65504.0f);

            // test minimum positive normal float16 value
            float minNormalF16 = std::ldexpf(1.f, -14); // 2^-14
            parsedFloat = Float16(minNormalF16);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 1 && parsedFloat.mantissa == 0 && val == minNormalF16);

            // value closest to pi
            parsedFloat = Float16(3.140625f);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 16 && parsedFloat.mantissa == 0b1001001000 && val == 3.140625f);

            // check rounding
            float expectedFloat = asfloat(0x40493FDB);
            parsedFloat = Float16(expectedFloat);
            uint16_t rawVal = parsedFloat.raw();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 16 && parsedFloat.mantissa == 0b1001001010 && rawVal == 0x424A);

            expectedFloat = asfloat(0x407FF000);
            parsedFloat = Float16(expectedFloat);
            rawVal = parsedFloat.raw();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 17 && parsedFloat.mantissa == 0 && rawVal == 0x4400);

            // value 1
            parsedFloat = Float16(1.f);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 15 && parsedFloat.mantissa == 0 && val == 1.0f);

            parsedFloat = Float16(1.00097656f);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 15 && parsedFloat.mantissa == 1 && val == 1.00097656f);
        }

        TEST_METHOD(FP16Subnormals)
        {
            /* testing subnormals */
            // test subnormal float16 value
            for (int i = 0; i < 1024; ++i)
            {
                float subnormal = std::ldexpf(float(i), -24);
                auto parsedFloat = Float16(subnormal);
                auto val = parsedFloat.value();
                Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == i && val == subnormal);
            }
        }
    };
}
