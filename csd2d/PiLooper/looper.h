#pragma once

#include "encoder.h"
#include "button.h"
#include "delayLine.h"

typedef unsigned int uint;

class Looper {
	
public:

	Looper(uint samplerate_in);
	~Looper();
	void write(float val_in) {del1.write(val_in * (float)recordState + del1.read());}
	float read() {return del1.read();}
	void tick();
	void erase();

private:

	void checkButton();
	void checkEncoder();
	inline void setAmp(float amp_in) {amp = amp_in;}
	inline float getAmp() {return amp;}
	void setRecodState(int state_in) {recordState = state_in;}
	
	Encoder enc1{9, 13};
	Button but1{16};
	DelayLine del1{44100 * 2};
	int recordState = 1;
	float amp = 1.0;
	int buttonEncoderCheckIndex = 0;
	int buttonEncoderCheckNr = 10;
};
