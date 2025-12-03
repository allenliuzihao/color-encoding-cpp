#include "pch.h"

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

void test_fp16_encoding()
{
    auto parsedFloat = Float16(65504);
    parsedFloat.print();
    assert(parsedFloat.sign == 0 && parsedFloat.exponent == 130 && parsedFloat.mantissa == 4587520);
}

int main() 
{
    print_binary_test();
    test_float32_encoding();
    test_fp16_encoding();
}