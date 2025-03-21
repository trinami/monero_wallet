#include "address.hpp"

void createMoneroAddress(const uint8_t* publicSpendKey, const uint8_t* publicViewKey, char* address) {
    uint8_t addressBin[69];
    addressBin[0] = 0x12;
    memcpy(addressBin + 1, publicSpendKey, 32);
    memcpy(addressBin + 33, publicViewKey, 32);
    
    uint8_t hash[32];
    keccak256_hash(addressBin, 65, hash);
    
    memcpy(addressBin + 65, hash, 4);
    
    base58encode(addressBin, 69, address);
} 