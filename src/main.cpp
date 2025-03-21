#include <esp_efuse.h>
#include <Arduino.h>
#include <SHA3.h>
#include <BLAKE2s.h>
#include <SHA384.h>
#include <RNG.h>
#include <qrcode.h>
#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <esp_system.h>
#include <esp_efuse.h>
#include <esp_efuse_table.h>

#include "utils/clear_screen.hpp"
#include "utils/mnemonic.hpp"
#include "crypto/hash/keccak256_hash.hpp"
#include "crypto/ecc/reduce.hpp"
#include "crypto/monero/keygen.hpp"
#include "utils/base58.hpp"
#include "crypto/monero/address.hpp"
#include "crypto/hash/whirlpool.hpp"
#include "globals.hpp"
#include "utils/print_colored.hpp"

XRNG xrng;

void setup() {
  Serial.begin(115200);
  delay(4000);

	RNG.begin(RNG_STARTVALUE);
	RNG.addNoiseSource(xrng);

  pinMode(9, INPUT_PULLUP);
  int i = 0;
  while(digitalRead(9) == HIGH)
  {
    if(i % 25 == 0)
    {
      clearScreen();

      /*bool secure_boot_enabled = esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_EN);
      Serial.print("Secure Boot:   ");
      if (secure_boot_enabled) {
        printlnColored(ANSI_GREEN, "ENABLED");
      } else {
        printlnColored(ANSI_RED, "DISABLED");
      }*/

      bool dis_download_mode_enabled = esp_efuse_read_field_bit(ESP_EFUSE_DIS_DOWNLOAD_MODE);
      Serial.print("Download mode: ");
      if (dis_download_mode_enabled) {
        printlnColored(ANSI_GREEN, "DISABLED");
      } else {
        printlnColored(ANSI_RED, "ENABLED");
      }

      const esp_partition_t* running = esp_ota_get_running_partition();
      if (running == nullptr) {
          Serial.println("Error getting running partition");
          return;
      }

      uint8_t sha256[32] = {0};  
      esp_partition_get_sha256(running, sha256);

      Serial.print("Current Firmware Hash (SHA-256): ");
      for (int i = 0; i < 32; i++)
      {
        if (sha256[i] < 0x10)
        {
          Serial.print("0");
        }
        Serial.print(sha256[i], HEX);
      }
      Serial.println();
      Serial.println();
      Serial.println("Press boot key to start...");
    }
    delay(20);
    i++;
  }
  delay(500);
}

void loop() {
  clearScreen();
	Serial.println("Generating...");
	while(!RNG.available(32)){RNG.loop();};
	
	uint8_t testSeed[32];
	RNG.rand(testSeed, 32);

  char mnemonicPhrase[25 * LONGEST_WORD + 25];
  getPhrase(testSeed, mnemonicPhrase);
  clearScreen();
  Serial.println(mnemonicPhrase);
  Serial.println("");

  uint8_t publicSpendKey[32];
  uint8_t publicViewKey[32];
  deriveMoneroKeys(testSeed, publicSpendKey, publicViewKey);
  
  /*Serial.print("Public Spend Key: ");
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
  Serial.println();*/
  
  Serial.println("Press boot key to continue...");
  delay(1000);
  while(digitalRead(9) == HIGH)
  {
    delay(10);
  }
  clearScreen();
  char moneroAddress[96+1];
  createMoneroAddress(publicSpendKey, publicViewKey, moneroAddress);
  moneroAddress[96] = '\0';
  Serial.print("Monero Address: ");
  Serial.println(moneroAddress);
  Serial.println();
  
  // Prepare monero address with prefix for QR code
  char qrAddress[110];
  strcpy(qrAddress, "monero:");
  strcat(qrAddress, moneroAddress);

  QRCode qrcode;
  uint8_t qrcodeBytes[qrcode_getBufferSize(5)];
  qrcode_initText(&qrcode, qrcodeBytes, 5, ECC_LOW, qrAddress);
  for(uint8_t i = 0; i < qrcode.size+2; i++)
  {
    printColored(ANSI_WHITE, "██");
  }
  Serial.println();
  for (uint8_t y = 0; y < qrcode.size; y++) {
    printColored(ANSI_WHITE, "██");
    for (uint8_t x = 0; x < qrcode.size; x++) {
        if (qrcode_getModule(&qrcode, x, y)) {
          Serial.print("  ");
        } else {
            printColored(ANSI_WHITE, "██");
        }
    }
    printColored(ANSI_WHITE, "██");
    Serial.println();
  }
  for(uint8_t i = 0; i < qrcode.size+2; i++)
  {
    printColored(ANSI_WHITE, "██");
  }
  Serial.println();
  Serial.println();
  Serial.println("Press boot key to generate another...");
  delay(1000);

  while(digitalRead(9) == HIGH)
  {
    delay(10);
  }
}
