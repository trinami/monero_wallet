#pragma once

#include <Arduino.h>
#include <Crypto.h>
#include <crypto/ecc/Ed25519_edit.hpp>
#include <utility/LimbUtil.h>
#include "crypto/hash/keccak256_hash.hpp"
#include "crypto/ecc/reduce.hpp"

void generateMoneroPublicKey(const uint8_t* privateKey, uint8_t* publicKey);
void deriveMoneroKeys(const uint8_t* privateSeed, uint8_t* publicSpendKey, uint8_t* publicViewKey);
void calculatePublicSpendKey(const uint8_t* privateSeed, uint8_t* publicSpendKey); 