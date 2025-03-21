#include "xrng.hpp"
#include <Arduino.h>
#include <Crypto.h>
#include <SHA512.h>
#include <BLAKE2s.h>
#include <crypto/hash/whirlpool.hpp>
#include "RNG.h"

#define NOISE_NOT_CALIBRATING 0
#define NOISE_CALIBRATING	  1

XRNG::XRNG(): calibratingState(NOISE_CALIBRATING) {
	pinMode(ADC_PIN, INPUT);
	analogSetPinAttenuation(ADC_PIN, ADC_2_5db);
	digitalWrite(ADC_PIN, LOW);
}

XRNG::~XRNG() {

}

void XRNG::added()
{

}

bool XRNG::calibrating() const
{
	return calibratingState != NOISE_NOT_CALIBRATING;
}

bool XRNG::getRandomBit()
{
	while(true)
	{
		bool bit1, bit2;
		bit1 = 0x1 & analogRead(ADC_PIN);
		
		//https://espressif-docs.readthedocs-hosted.com/projects/esp-faq/en/latest/software-framework/peripherals/adc.html
		delayMicroseconds(1500);

		bit2 = 0x1 & analogRead(ADC_PIN);
		
		if(bit1 != bit2)
		{
			return bit1;
		}
	
		delayMicroseconds(1500);
	}
}

uint8_t XRNG::getRandomByte() {
	uint8_t rnd = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		rnd |= (getRandomBit() << i);
	}

	return rnd;
}

void XRNG::stir() {
	calibratingState = NOISE_CALIBRATING;
	uint8_t buffer[32] = {0};
	uint8_t random_pool[POOL_SIZE] = {0};

	esp_fill_random(random_pool, POOL_SIZE);
	for(int i = 0; i < POOL_SIZE; i++)
	{
		random_pool[i] ^= getRandomByte();
	}
	sha3.update(random_pool, sizeof(POOL_SIZE));
	sha3.finalize(random_pool, sha3.hashSize());

	for(int i = 0; i < POOL_SIZE; i++)
	{
		random_pool[i] ^= getRandomByte();
	}
	whirlpool.update(random_pool, sizeof(POOL_SIZE));
	whirlpool.finalize(random_pool);

	blake2s.update(random_pool, sizeof(POOL_SIZE));
	blake2s.finalize(buffer, 32);

	output(buffer, 32, 128);
	calibratingState = NOISE_NOT_CALIBRATING;
}
