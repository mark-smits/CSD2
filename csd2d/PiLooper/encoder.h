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
		void checkPins();
		int getVal();
		void setVal(int val_in);

	private:

		int lPin, rPin;
		int val = 0;
		int minVal = 0, maxVal = 10;
		int lPinLastState = 0;

};


