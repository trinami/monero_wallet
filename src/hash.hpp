#pragma once

#include <Arduino.h>
#include <KeccakCore.h>

uint32_t crc32(const char *s, size_t length);
void keccak256_hash(const uint8_t* input, size_t input_len, uint8_t* output); 