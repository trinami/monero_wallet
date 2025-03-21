#pragma once

#include <Arduino.h>
#include <KeccakCore.h>

void keccak256_hash(const uint8_t* input, size_t input_len, uint8_t* output); 
