#pragma once

#include <Arduino.h>
#include "utils/base58.hpp"
#include "crypto/hash/keccak256_hash.hpp"

void createMoneroAddress(const uint8_t* publicSpendKey, const uint8_t* publicViewKey, char* address); 