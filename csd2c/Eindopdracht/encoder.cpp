#include "encoder.h"
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>

Encoder::Encoder(int lPin, int rPin) : lPin(lPin), rPin(rPin) {
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

void Encoder::checkPins() {
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

void Encoder::setVal(int val_in) {
	val = val_in;
	clip();
}
