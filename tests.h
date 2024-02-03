#pragma once

#include <cstdint>

extern "C" {
float testAdd(float a, float b);
void testMultiply(char *str_p);
void testArray(uint8_t *in, uint8_t size, uint8_t delta);
}
