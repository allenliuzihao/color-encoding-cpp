#include "pch.h"

void print_binary_test()
{
    print_binary(0x07804000);
    print_binary(0x7F800000);
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

int main() 
{
    test_float32_encoding();
}