#ifndef _SAW_H_
#define _SAW_H_

#include <iostream>

class Saw {
public:
  Saw(float frequency, float samplerate);
  ~Saw();
  
  void setFrequency(float freq_in);
  float getFrequency();
  float getSample();
  void tick();

protected:
  float samplerate;
  float frequency;
  float phase;
  float sample;

};

#endif
