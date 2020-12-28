#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include "oscillator.h"

#pragma once

class Sine : public Oscillator
{
public:
  //constructor and destructor
  Sine(float frequency, double samplerate);
  ~Sine();

  //override the calc function
  void calc();
  //setters & getters
  void setShaper(float value, float dw);
  float getShaperValue();
  float getShaperDW();
private:
  float shaperValue;
  float shaperDW;
};

#endif
