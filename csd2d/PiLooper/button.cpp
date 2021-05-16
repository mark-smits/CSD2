#include "button.h"
#include <stdio.h>
#include <wiringPi.h>
#include <iostream>

Button::Button(int pin) : pin_nr(pin) {
	wiringPiSetup();
	pinMode(pin, INPUT);
}

int Button::readPin() {
	return digitalRead(pin_nr);
}

void Button::checkPin() {
	val = readPin();
}
