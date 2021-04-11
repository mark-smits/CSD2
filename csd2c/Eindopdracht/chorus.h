#pragma once

#include "delayLine.h"
#include "effect.h"

typedef unsigned int uint;

class Chorus : public Effect {

public:

  Chorus(uint rate);
  ~Chorus();
  
  void write(float val_in);
  float read();
  void tick();

private:

  uint sinIndex;
  DelayLine del1{12.0*getSamplerate()/1000.0}, del2{12.0*getSamplerate()/1000.0}, del3{12.0*getSamplerate()/1000.0};
  float mix1 = 0.6, mix2 = 0.6, mix3 = 0.6;
  float phase1 = 0.0, phase2 = 0.0, phase3 = 0.0;
  float del1Dist = 3.5, del2Dist = 3.5, del3Dist = 3.5, del1Rate = 0.41, del2Rate = 0.59, del3Rate = 7.9;
  float interp, tap1 = 0.0, tap2 = 0.0, tap3 = 0.0;
  float sinus[101];
  float sinusValue1 = 0, sinusValue2 = 0, sinusValue3 = 0;
  float delAverageDist = 3.5, del1ModDepth = 1.84, del2ModDepth = 1.84, del3ModDepth = 0.25;
  float samplerateMillisec = getSamplerate()/1000.0;
  
  void phaseIncrease();
  void sinusCalculation();
  void distanceCalculation();
};
