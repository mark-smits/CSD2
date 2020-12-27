#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

#pragma once

class Oscillator {
public:
  //constructor & destructor
  Oscillator(float frequency, double samplerate);
  ~Oscillator();

  //calulations and incrementation
  void tick();
  virtual void calc();

  //setters & getters
  void setFrequency(float freq);
  float getFrequency();
  void setAmp(float amp);
  void setSample(float samp);
  float getSample();
  float getPhase();

private:
  double samplerate;
  float amplitude;
  float frequency;
  float phase;
  float sample;
};

#endif
