#pragma once

#include <cstring>

/**
 * Sichere Methode zum Löschen von Speicher
 * @param ptr Zeiger auf den zu löschenden Speicherbereich
 * @param len Länge des zu löschenden Speicherbereichs in Bytes
 */
inline void memzero(void* ptr, size_t len) {
    //that compiler should not optimize out the memset
    volatile uint8_t* p = static_cast<volatile uint8_t*>(ptr);
    while (len--) {
        *p++ = 0;
    }
}
