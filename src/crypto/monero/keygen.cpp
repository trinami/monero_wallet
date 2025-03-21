#include "keygen.hpp"

void generateMoneroPublicKey(const uint8_t* privateKey, uint8_t* publicKey) {
    limb_t scalar[NUM_LIMBS_256BIT];
    BigNumberUtil::unpackLE(scalar, NUM_LIMBS_256BIT, privateKey, 32);

    Ed25519::Point result;
    Ed25519::mul(result, scalar, true);

    Ed25519::encodePoint(publicKey, result);

    clean(result);
    clean(scalar);
}

void deriveMoneroKeys(const uint8_t* privateSeed, uint8_t* publicSpendKey, uint8_t* publicViewKey) {
    uint8_t secretSpendKey[32];
    uint8_t secretViewKey[32];
    
    memcpy(secretSpendKey, privateSeed, 32);
    sc_reduce32(secretSpendKey);
    
    /*Serial.print("Private Spend Key: ");
    for (int i = 0; i < 32; i++) {
        if (secretSpendKey[i] < 0x10) Serial.print("0");
        Serial.print(secretSpendKey[i], HEX);
    }
    Serial.println();*/
    
    keccak256_hash(secretSpendKey, 32, secretViewKey);
    
    sc_reduce32(secretViewKey);
    
    /*Serial.print("Private View Key: ");
    for (int i = 0; i < 32; i++) {
        if (secretViewKey[i] < 0x10) Serial.print("0");
        Serial.print(secretViewKey[i], HEX);
    }
    Serial.println();*/
    
    generateMoneroPublicKey(secretSpendKey, publicSpendKey);
    
    generateMoneroPublicKey(secretViewKey, publicViewKey);
}

void calculatePublicSpendKey(const uint8_t* privateSeed, uint8_t* publicSpendKey) {
    uint8_t pkey_hash[32];
    keccak256_hash(privateSeed, 32, pkey_hash);

    uint8_t secretSpendKey[32];
    memcpy(secretSpendKey, privateSeed, 32);

    Ed25519::derivePublicKey(publicSpendKey, secretSpendKey);
} 