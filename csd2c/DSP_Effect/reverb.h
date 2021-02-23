#pragma once

#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include "chorus.h"
#include <cstring>
#include <iostream>

typedef unsigned int uint;

class Reverb {

public:

  // constructor & destructor
  Reverb(uint samplerate);
  ~Reverb();

  // setters & getters
  inline void setFB(float fb_in){ feedback = fb_in; }
  inline float getFB(){ return feedback; }
  void setdw(float val_in);

  // reverb functions
  void tick();
  void write(float val_in);
  float read(float val_in);

private:

  float feedback, drywet, dlvl, wlvl;
  AllPassFilter apf1, apf2, apf3, apf4, apf5, apf6;
  DelayLine del;
  BQFilter lpf;
  Chorus chor;
  float tapc, tap1, tap2, tap3, tap4, tapd, tapf, tap5, tap6;
};
