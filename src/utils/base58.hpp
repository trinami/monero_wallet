#pragma once

#include <Arduino.h>

void base58encode(const uint8_t* input, size_t input_len, char* output);

extern const char* BASE58_ALPHABET; 