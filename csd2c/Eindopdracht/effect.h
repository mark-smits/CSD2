#pragma once

typedef unsigned int uint;

class Effect {
public:
	Effect();
	Effect(uint rate);
	~Effect();
	virtual float read();
	virtual void write(float val_in);
	virtual void tick();
	uint getSamplerate();
private:
	uint samplerate;
};
