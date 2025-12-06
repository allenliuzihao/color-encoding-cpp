#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestFP32)
	{
	public:
		TEST_METHOD(TestFP32EncodeAndDecode)
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

            float expectedVal = powf(2.0f, -149);
            parsedFloat = Float32(expectedVal);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 1 && val == expectedVal);

            parsedFloat = Float32(0);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 0 && val == 0.0f);

            parsedFloat = Float32(asfloat(0x7f800000));
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0);

            parsedFloat = Float32(asfloat(0xff800000));
            Assert::IsTrue(parsedFloat.sign == 1 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0);

            parsedFloat = Float32(asfloat(0x7f800001));
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 1);

            parsedFloat = Float32(12.375);
            val = parsedFloat.value();
            Assert::IsTrue(parsedFloat.sign == 0 && parsedFloat.exponent == 130 && parsedFloat.mantissa == 4587520 && val == 12.375);
		}
	};
}
