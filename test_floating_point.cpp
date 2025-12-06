#include "pch.h"
#include "test_floating_point.h"

void print_binary_test()
{
    auto str1 = binary_string(uint32_t(0x07804000));
    assert(str1 == "00000111100000000100000000000000");

    auto str2 = binary_string(uint32_t(0x7F800000));
    assert(str2 == "01111111100000000000000000000000");

    auto str3 = binary_string(uint16_t(0x8000));
    assert(str3 == "1000000000000000");

    auto str4 = binary_string(uint16_t(0xf010));
    assert(str4 == "1111000000010000");

    auto str5 = binary_string(uint16_t(0xfffa));
    assert(str5 == "1111111111111010");
}

void test_float32_encoding()
{
    Float32 parsedFloat = Float32(0.5);
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 126 && parsedFloat.mantissa == 0);
    parsedFloat.print();

    parsedFloat = Float32(-0.5);
    assert(parsedFloat.sign == 1 && parsedFloat.exponent == 126 && parsedFloat.mantissa == 0);
    parsedFloat.print();

    parsedFloat = Float32(0.15625);
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 124 && parsedFloat.mantissa == 2097152);

    parsedFloat = Float32(powf(2.0f, -149));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 1);

    parsedFloat = Float32(0);
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 0 && parsedFloat.mantissa == 0);

    parsedFloat = Float32(asfloat(0x7f800000));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0);

    parsedFloat = Float32(asfloat(0xff800000));
    parsedFloat.print();
    assert(parsedFloat.sign == 1 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 0);

    parsedFloat = Float32(asfloat(0x7f800001));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 0xff && parsedFloat.mantissa == 1);

    parsedFloat = Float32(12.375);
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 130 && parsedFloat.mantissa == 4587520);
}

void test_fp16_special_numbers()
{
    std::cout << "test fp16 special numbers\n";

    /* testing special numbers */
    auto parsedFloat = Float16(float(65505));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023);

    parsedFloat = Float16(float(-65505));
    parsedFloat.print();
    assert(parsedFloat.sign == 1 && parsedFloat.exponent == 30 && parsedFloat.mantissa == 1023);

    parsedFloat = Float16(float(65520));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0);

    parsedFloat = Float16(float(65521));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0);

    parsedFloat = Float16(float(-65521));
    parsedFloat.print();
    assert(parsedFloat.sign == 1 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0);

    parsedFloat = Float16(float(125521));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 0);

    parsedFloat = Float16(asfloat(0x7f800001));
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 31 && parsedFloat.mantissa == 1);

}

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