#include <cstdint>
#include <iostream>
#include <sstream>

#include "tests.h"

float testAdd(float a, float b) { return a + b; }

using multiply = float(float a, float b);

float callMultiply(uint64_t num_p, float a, float b) { return ((multiply *)num_p)(a, b); }

void testMultiply(char *str_p) {
    uint64_t num_p;
    std::istringstream(str_p) >> num_p;
    std::cout << "multiply: " << callMultiply(num_p, 25.0, 12.0) << std::endl;
}

void testArray(uint8_t *in, uint8_t size, uint8_t delta) {
    for (int i = 0; i < size; ++i) {
        in[i] = in[i] + delta;
    }
}
