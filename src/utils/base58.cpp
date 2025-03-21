#include "base58.hpp"

const char* BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

void base58encode(const uint8_t* input, size_t input_len, char* output) {
    size_t output_pos = 0;
    size_t block_size = 8;
    size_t full_blocks = input_len / block_size;
    size_t last_block_size = input_len % block_size;

    for (size_t i = 0; i < full_blocks; i++) {
        uint8_t block[8];
        memcpy(block, input + i * block_size, block_size);

        char block_output[12] = {0};
        size_t block_output_len = 0;
        uint8_t digits[11] = {0};

        for (size_t j = 0; j < block_size; j++) {
            uint16_t carry = block[j];
            for (size_t k = 0; k < block_output_len || carry; k++) {
                if (k >= block_output_len) {
                    block_output_len = k + 1;
                }
                carry += 256 * digits[k];
                digits[k] = carry % 58;
                carry /= 58;
            }
        }

        for (size_t j = 0; j < block_output_len; j++) {
            block_output[j] = BASE58_ALPHABET[digits[block_output_len - 1 - j]];
        }

        while (block_output_len < 11) {
            block_output[block_output_len++] = '1';
        }

        memcpy(output + output_pos, block_output, 11);
        output_pos += 11;
    }

    if (last_block_size > 0) {
        uint8_t block[5] = {0};
        memcpy(block, input + full_blocks * block_size, last_block_size);

        char block_output[8] = {0};
        size_t block_output_len = 0;
        uint8_t digits[7] = {0};

        for (size_t j = 0; j < last_block_size; j++) {
            uint16_t carry = block[j];
            for (size_t k = 0; k < block_output_len || carry; k++) {
                if (k >= block_output_len) {
                    block_output_len = k + 1;
                }
                carry += 256 * digits[k];
                digits[k] = carry % 58;
                carry /= 58;
            }
        }

        for (size_t j = 0; j < block_output_len; j++) {
            block_output[j] = BASE58_ALPHABET[digits[block_output_len - 1 - j]];
        }

        while (block_output_len < 7) {
            block_output[block_output_len++] = '1';
        }

        memcpy(output + output_pos, block_output, 7);
        output_pos += 7;
    }

    output[output_pos] = '\0';
} 