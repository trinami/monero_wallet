#include "keccak256_hash.hpp"

void keccak256_hash(const uint8_t* input, size_t input_len, uint8_t* output) {
    KeccakCore keccak;
    keccak.setCapacity(256 * 2);
    keccak.reset();
    keccak.update(input, input_len);
    keccak.pad(0x01);
    keccak.extract(output, 32);
} 