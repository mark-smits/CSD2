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
	checkButton();
	checkEncoder();
}

void Looper::checkButton(){
	
}

void Looper::checkEncoder(){
	
}

void Looper::erase(){
	del1.clean();
}
