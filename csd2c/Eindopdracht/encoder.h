#pragma once

#include <wiringPi.h>
#include <iostream>
#include <stdio.h>

class Encoder {

	public:

		Encoder(int lPin, int rPin);
		~Encoder();

		int readPin(int pin);
		void setMaxVal(int maxInput);
		void setMinVal(int minInput);
		void clip();
		void tick();
		int getVal();

	private:

		int lPin, rPin;
		int val;
		int minVal, maxVal;
		int lPinLastState;

};


