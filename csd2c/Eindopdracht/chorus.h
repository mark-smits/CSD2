#pragma once

#include "delayLine.h"

class Chorus {

public:

  Chorus(int rate);
  ~Chorus();
  
  void write(float val_in);
  float read();
  void tick();

private:

  DelayLine del1{10*samplerate/1000}, del2{10*samplerate/1000}, del3{10*samplerate/1000};
  float mix1 = 0.6, mix2 = 0.6, mix3 = 0.6;
  float phase1 = 0.0, phase2 = 0.0, phase3 = 0.0;
  float del1Dist = 3.5, del2Dist = 3.5, del3Dist = 3.5, del1Rate = 0.41, del2Rate = 0.59, del3Rate = 7.9;
  float interp, tap1 = 0.0, tap2 = 0.0, tap3 = 0.0;
  float sinus[101];
  float sinusValue1 = 0, sinusValue2 = 0, sinusValue3 = 0;
  int samplerate, sinIndex;

  void phaseIncrease();
  void sinusCalculation();
  void distanceCalculation();
};
