#pragma once

#include <Arduino.h>

static uint64_t load_3(const unsigned char *in);
static uint64_t load_4(const unsigned char *in);
void sc_reduce(unsigned char *s);
void sc_reduce32(unsigned char *s);

extern const uint8_t L[32]; 