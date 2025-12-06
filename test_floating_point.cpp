#include "pch.h"
#include "test_floating_point.h"

void test_fp16_normal_numbers()
{
    std::cout << "test fp16 normal numbers\n";

    /* testing normal numbers */
    // test maximum float16 value
    auto parsedFloat = Float16(float(65504));
    parsedFloat.print();
    float val = parsedFloat.value();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && val == 65504.0f);

    parsedFloat = Float16(float(-65504));
    parsedFloat.print();
    val = parsedFloat.value();
    assert(parsedFloat.sign == 1 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023 && val == -65504.0f);

    // test minimum positive normal float16 value
    float minNormalF16 = std::ldexpf(1.f, -14); // 2^-14
    parsedFloat = Float16(minNormalF16);
    parsedFloat.print();
    val = parsedFloat.value();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 1 && parsedFloat.mantissa == 0 && val == minNormalF16);

    // value closest to pi
    parsedFloat = Float16(3.140625f);
    parsedFloat.print();
    val = parsedFloat.value();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 16 && parsedFloat.mantissa == 0b1001001000 && val == 3.140625f);

    // value 1
    parsedFloat = Float16(1.f);
    parsedFloat.print();
    val = parsedFloat.value();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 15 && parsedFloat.mantissa == 0 && val == 1.0f);

    parsedFloat = Float16(1.00097656f);
    parsedFloat.print();
    val = parsedFloat.value();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 15 && parsedFloat.mantissa == 1 && val == 1.00097656f);
}

void test_fp16_subnormals()
{
    std::cout << "test fp16 subnormal numbers\n";

    /* testing subnormals */
    // test subnormal float16 value
    for (int i = 0; i < 1024; ++i)
    {
        float subnormal = std::ldexpf(float(i), -24);
        auto parsedFloat = Float16(subnormal);
        auto val = parsedFloat.value();
        assert(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == i && val == subnormal);
    }
}