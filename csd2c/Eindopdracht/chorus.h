#pragma once

#include "delayLine.h"

class Chorus {

public:

  // constructor & destructor
  Chorus(int samplerate);
  ~Chorus();

  // setters & getters


  // chorus functions
  void write(float val_in);
  float read();
  void tick();

private:

  DelayLine del1, del2, del3;
  float mix1, mix2, mix3;
  float phase1, phase2, phase3;
  float del1Dist, del2Dist, del3Dist, del1Rate, del2Rate, del3Rate;
  float interp, tap1, tap2, tap3;
  float sinus[101];
  int samplerate, sinIndex;

};
