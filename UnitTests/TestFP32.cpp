#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestFP32)
	{
	public:
        TEST_METHOD(FP32Specials)
        {
            auto parsedFloat = Float32(0);
            auto val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 0 && val == 0.0f);

            auto expectedFloat = asfloat(0x7f800000);
            parsedFloat = Float32(expectedFloat);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0 && expectedFloat == val);

            expectedFloat = asfloat(0xff800000);
            parsedFloat = Float32(expectedFloat);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0 && expectedFloat == val);

            expectedFloat = asfloat(0x7f800001);
            parsedFloat = Float32(expectedFloat);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 1 && std::isnan(val));
        }

		TEST_METHOD(FP32Normals)
		{
            Float32 parsedFloat = Float32(0.5);
            float val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 126 && parsedFloat.mantissa == 0 && val == 0.5f);

            parsedFloat = Float32(-0.5);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 126 && parsedFloat.mantissa == 0 && val == -0.5f);

            parsedFloat = Float32(0.15625);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 124 && parsedFloat.mantissa == 2097152 && val == 0.15625f);
            
            parsedFloat = Float32(12.375);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 130 && parsedFloat.mantissa == 4587520 && val == 12.375);
		}

        TEST_METHOD(FP32Subnormals)
        {
            float expectedVal = powf(2.0f, -149);
            auto parsedFloat = Float32(expectedVal);
            auto val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 1 && val == expectedVal);
        }
	};
}
