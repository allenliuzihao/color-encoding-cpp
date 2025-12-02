#include "pch.h"

void print_binary_test()
{
    print_binary(0x07804000);
    print_binary(0x7F800000);
}

void test_float32_encoding()
{
    Float32 parsedFloat = parse_float32(0.5);
    parsedFloat.print();
}

int main() 
{
    test_float32_encoding();
}