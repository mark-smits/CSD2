#include "encoder.h"
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>

Encoder::Encoder(int lPin, int rPin) : lPin(lPin), rPin(rPin) {
	this->minVal = 0;
	this->maxVal = 10;
	this->val = 0;
	this->lPinLastState = 0;
	wiringPiSetup();
	pinMode(lPin, INPUT);
	pinMode(rPin, INPUT);
}

Encoder::~Encoder() {
	
}

int Encoder::readPin(int pin) {
	return digitalRead(pin);
}

void Encoder::setMinVal(int minInput) {
	if (minInput > maxVal) {
		minInput = maxVal;
	}
	minVal = minInput;
}

void Encoder::setMaxVal(int maxInput) {
	if (maxInput < minVal) {
		maxInput = minVal;
	}
	maxVal = maxInput;
}

void Encoder::clip() {
	if (val > maxVal) {
		val = maxVal;
	}
	else if (val < minVal) {
		val = minVal;
	}
}

void Encoder::tick() {
	if (readPin(lPin) == 1 && readPin(lPin) != lPinLastState) {
		if (readPin(rPin) == 1) {
			val++;
		}
		else {
			val--;
		}
	}
	clip();
	lPinLastState = readPin(lPin);
}

int Encoder::getVal() {
	return val;
}
