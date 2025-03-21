#pragma once

#include <Arduino.h>

#include "NoiseSource.h"
#include "globals.hpp"

#define POOL_SIZE 64
#define ADC_PIN 3

class XRNG: public NoiseSource {
	public:
		explicit XRNG();
		virtual ~XRNG();

		bool calibrating() const;
		
		void added();
		void stir();

	private:
		uint8_t calibratingState;
		bool getRandomBit();
		uint8_t getRandomByte();
		uint8_t pool[POOL_SIZE];
};
