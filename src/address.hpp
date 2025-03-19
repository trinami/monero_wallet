#pragma once

#include <Arduino.h>
#include "base58.hpp"
#include "hash.hpp"

void createMoneroAddress(const uint8_t* publicSpendKey, const uint8_t* publicViewKey, char* address); 