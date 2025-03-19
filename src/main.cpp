#include <Arduino.h>
#include "mnemonic.hpp"
#include "hash.hpp"
#include "reduce.hpp"
#include "keygen.hpp"
#include "base58.hpp"
#include "address.hpp"
#include <qrcode.h>

void setup() {
  Serial.begin(115200);
  delay(5000);

  Serial.println("Starting...");

  uint8_t testSeed[32] = {
    0x9f, 0x86, 0xd0, 0x81, 0x88, 0x4c, 0x7d, 0x65,
    0x9a, 0x2f, 0xea, 0xa0, 0xc5, 0x5a, 0xd0, 0x15,
    0xa3, 0xbf, 0x4f, 0x1b, 0x2b, 0x0b, 0x82, 0x2c,
    0xd1, 0x5d, 0x6c, 0x15, 0xb0, 0xf0, 0x0a, 0x08
  };
  
  char mnemonicPhrase[25 * LONGEST_WORD + 25];
  getPhrase(testSeed, mnemonicPhrase);
  Serial.println("Generated mnemonic phrase:");
  Serial.println(mnemonicPhrase);

  uint8_t publicSpendKey[32];
  uint8_t publicViewKey[32];
  deriveMoneroKeys(testSeed, publicSpendKey, publicViewKey);
  
  Serial.print("Public Spend Key: ");
  for (int i = 0; i < 32; i++) {
    if (publicSpendKey[i] < 0x10) Serial.print("0");
    Serial.print(publicSpendKey[i], HEX);
  }
  Serial.println();
  
  Serial.print("Public View Key: ");
  for (int i = 0; i < 32; i++) {
    if (publicViewKey[i] < 0x10) Serial.print("0");
    Serial.print(publicViewKey[i], HEX);
  }
  Serial.println();
  
  char moneroAddress[95+1];
  createMoneroAddress(publicSpendKey, publicViewKey, moneroAddress);
  moneroAddress[95] = '\0';
  Serial.print("Monero Address: 4");
  Serial.println(moneroAddress);
  
  // Prepare monero address with prefix for QR code
  char qrAddress[110];
  strcpy(qrAddress, "monero:4");
  strcat(qrAddress, moneroAddress);
  
  /*QRCode qrcode;
  uint8_t qrcodeBytes[qrcode_getBufferSize(4)];
  qrcode_initText(&qrcode, qrcodeBytes, 6, ECC_MEDIUM, qrAddress);
  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
        if (qrcode_getModule(&qrcode, x, y)) {
          Serial.print("  ");
        } else {
            Serial.print("\033[47m██\033[0m");
        }
    }
    Serial.println("");
  }*/
}

void loop() {
}
