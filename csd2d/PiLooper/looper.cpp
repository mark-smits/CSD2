#include "encoder.h"
#include "button.h"
#include "delayLine.h"
#include "looper.h"

Looper::Looper(uint samplerate_in){
	del1.setDistance(samplerate_in * 1);
}

Looper::~Looper(){
	
}

void Looper::tick(){
	del1.tick();
	while (buttonEncoderCheckIndex >= buttonEncoderCheckNr) {
		checkButton();
		checkEncoder();
		buttonEncoderCheckIndex -= buttonEncoderCheckNr;
	}
	buttonEncoderCheckIndex++;
}

void Looper::checkButton(){
	but1.checkPin();
}

void Looper::checkEncoder(){
	enc1.checkPins();
}

void Looper::erase(){
	del1.clean();
}
