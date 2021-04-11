#include "effect.h"
#include <iostream>
#include <cstring>

Effect::Effect() : Effect(44100) {}

Effect::Effect(uint rate) : samplerate(rate) {
	
}

Effect::~Effect() {
	
}

void Effect::write(float val_in) {
	
}

float Effect::read() {
	
}

void Effect::tick(){
	
}

uint Effect::getSamplerate(){
	return samplerate;
}
