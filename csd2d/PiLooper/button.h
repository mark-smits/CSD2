#pragma once

typedef unsigned int uint;

class Button {
	
public:

	Button(int pin);
	~Button(){};
	
	void checkPin();
	int getVal(){return val;}

private:
	
	int readPin();
	int pin_nr;
	int val;
	int lastVal;
};
