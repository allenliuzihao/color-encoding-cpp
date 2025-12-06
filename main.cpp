#include "pch.h"
#include "test_floating_point.h"

void test_fp16_encoding()
{
    test_fp16_special_numbers();
    test_fp16_normal_numbers();
    test_fp16_subnormals();
}

int main() 
{
    print_binary_test();
    test_float32_encoding();
    test_fp16_encoding();
}