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
	void flipRecordState(){recordState = 1 - recordState;}
	void buttonEventHandler(uint current_val);
	void buttonOnEvent();
	void buttonOffEvent();
	void calculateLongPress();
	void longEventHandler();
	void shortEventHandler();
	
	uint samplerate;
	uint maxDelaySeconds = 10;
	uint maxDelaySize = samplerate * maxDelaySeconds;
	
	Encoder enc1{9, 13};
	Button but1{16};
	DelayLine del1{maxDelaySize * 2};
	
	int recordState = 0;
	float amp = 1.0;
	uint buttonEncoderCheckIndex = 0;
	uint buttonEncoderCheckNr = 10;
	uint buttonHoldCounter = 0;
	uint buttonCurrentVal = 0;
	uint buttonLastVal = 0;
	uint buttonHoldTime = 0;
	bool buttonHoldTimeCounting = false;
	bool hasBuffer = false;
	uint longPressThresh = 2 * samplerate/10;
	bool longPressCondition = false;
	uint delayDistanceCounter = 0;
	bool delayDistanceCounting = false;
	bool delayTicking = false;
};
