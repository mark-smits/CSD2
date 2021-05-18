#include "encoder.h"
#include "button.h"
#include "delayLine.h"
#include "looper.h"

Looper::Looper(uint samplerate_in) : samplerate(samplerate_in) {
	del1.setDistance(samplerate_in * 1 * maxDelaySeconds);
}

Looper::~Looper(){
	
}

void Looper::tick(){
	if (delayTicking) {
		del1.tick();
	}
	if (delayDistanceCounting) {
			delayDistanceCounter++;
	}
	
	while (buttonEncoderCheckIndex >= buttonEncoderCheckNr) {
		checkButton();
		checkEncoder();
		buttonEncoderCheckIndex -= buttonEncoderCheckNr;
		if (buttonHoldTimeCounting) {
			buttonHoldTime++;
		}
	}
	buttonEncoderCheckIndex++;
}

void Looper::checkButton(){
	but1.checkPin();
	buttonCurrentVal = but1.getVal();
	if (buttonCurrentVal != buttonLastVal){
		buttonEventHandler(buttonCurrentVal);
	}
	buttonLastVal = buttonCurrentVal;
}

void Looper::buttonEventHandler(uint current_val){
	if (current_val == 1){
		buttonOnEvent();
	}
	else {
		buttonOffEvent();
	}
}

void Looper::buttonOnEvent(){
	buttonHoldTime = 0;
	buttonHoldTimeCounting = true;
}

void Looper::buttonOffEvent(){
	buttonHoldTimeCounting = false;
	calculateLongPress();
	if (longPressCondition) {
		longEventHandler();
	} else {
		shortEventHandler();
	}
}

void Looper::longEventHandler(){
	erase();
	delayDistanceCounter = 0;
	hasBuffer = false;
	setRecodState(0);
	delayDistanceCounting = false;
	delayTicking = false;
	std::cout << "Loop cleared\n";
}

void Looper::shortEventHandler(){
	if (hasBuffer){
		flipRecordState();
		if (recordState == 1){
			std::cout << "Recording on\n";
		}else{
			std::cout << "Recording off\n";
		}
	} else {
		if (delayDistanceCounting) {
			delayDistanceCounting = false;
			if (delayDistanceCounter > maxDelaySize){
				std::cout << "buffer size exceeded, using max size\n";
				delayDistanceCounter = maxDelaySize;
			}
			del1.setDistance(delayDistanceCounter);
			setRecodState(0);
			std::cout << "Loop set\n";
			hasBuffer = true;
		} else {
			setRecodState(1);
			delayDistanceCounting = true;
			delayTicking = true;
			std::cout << "Loop started\n";
		}
	}
}

void Looper::calculateLongPress(){
	if (buttonHoldTime >= longPressThresh) {
		longPressCondition = true;
	} else {
		longPressCondition = false;
	}
}

void Looper::checkEncoder(){
	enc1.checkPins();
}

void Looper::erase(){
	del1.clean();
}
