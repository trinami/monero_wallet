#pragma once

//define CRYPTO_AES_DEFAULT

#include <Arduino.h>
#include <Crypto.h>
#include <SHA3.h>
#include <BLAKE2s.h>
#include "crypto/xrng.hpp"
#include "crypto/hash/whirlpool.hpp"

#define RNG_STARTVALUE "TRICRYPT1337"
#define MAX_INPUT_SIZE 128
#define LED_BUILTIN 8

extern char input[MAX_INPUT_SIZE+1];
extern SHA3_512 sha3;
extern uint8_t pass_hash[64];
extern BLAKE2s blake2s;
extern Whirlpool whirlpool;
