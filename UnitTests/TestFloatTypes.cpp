#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(TestFloatTypes)
    {
    public:
        TEST_METHOD(TestFloat3)
        {
            float3<float> vec = { 0.5f, 1.5f, -0.5f };
            Assert::AreEqual(0.5f, vec.x());
            Assert::AreEqual(1.5f, vec.y());
            Assert::AreEqual(-0.5f, vec.z());

            float3<double> vec1 = { -2.0, 0.0, 3.5 };
            Assert::AreEqual(-2.0, vec1.x());
            Assert::AreEqual(0.0, vec1.y());
            Assert::AreEqual(3.5, vec1.z());

            float3<Float32> vec2 = { 2.5f, -1.0f, 0.0f };
            Assert::AreEqual(2.5f, vec2.x().value());
            Assert::AreEqual(-1.0f, vec2.y().value());
            Assert::AreEqual(0.0f, vec2.z().value());

            float3<Float16> vec3 = { Float16(1.0f), Float16(-0.5f), Float16(3.0f) };
            Assert::AreEqual(1.0f, vec3.x().value());
            Assert::AreEqual(-0.5f, vec3.y().value());
            Assert::AreEqual(3.0f, vec3.z().value());
        }

        TEST_METHOD(TestFloat4)
        {
            
        }
    };
}
