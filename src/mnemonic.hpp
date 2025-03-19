#pragma once

#include <Arduino.h>
#include "mnemonic_words.hpp"

void loadWordFromPROGMEM(int index, char* buffer);
void getPhrase(const uint8_t* raw, char* mnemonic);

extern char word_buffer[LONGEST_WORD + 1]; 