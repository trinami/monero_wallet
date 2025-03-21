#pragma once

#include <Arduino.h>

// ANSI Escape Codes als constexpr-Strings (16 Basisfarben)
constexpr const char* ANSI_RESET         = "\x1B[0m";
constexpr const char* ANSI_BLACK         = "\x1B[30m";
constexpr const char* ANSI_RED           = "\x1B[31m";
constexpr const char* ANSI_GREEN         = "\x1B[32m";
constexpr const char* ANSI_YELLOW        = "\x1B[33m";
constexpr const char* ANSI_BLUE          = "\x1B[34m";
constexpr const char* ANSI_MAGENTA       = "\x1B[35m";
constexpr const char* ANSI_CYAN          = "\x1B[36m";
constexpr const char* ANSI_WHITE         = "\x1B[37m";
constexpr const char* ANSI_BRIGHT_BLACK  = "\x1B[90m";
constexpr const char* ANSI_BRIGHT_RED    = "\x1B[91m";
constexpr const char* ANSI_BRIGHT_GREEN  = "\x1B[92m";
constexpr const char* ANSI_BRIGHT_YELLOW = "\x1B[93m";
constexpr const char* ANSI_BRIGHT_BLUE   = "\x1B[94m";
constexpr const char* ANSI_BRIGHT_MAGENTA= "\x1B[95m";
constexpr const char* ANSI_BRIGHT_CYAN   = "\x1B[96m";
constexpr const char* ANSI_BRIGHT_WHITE  = "\x1B[97m";

inline void printlnColored(const char* color, const char* text) {
    Serial.print(color);
    Serial.print(text);
    Serial.println(ANSI_RESET);
}

inline void printColored(const char* color, const char* text) {
    Serial.print(color);
    Serial.print(text);
    Serial.print(ANSI_RESET);
}