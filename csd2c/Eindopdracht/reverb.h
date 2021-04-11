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
  void setTone(float val_in);
  void setSize(float val_in);

  // reverb functions
  void tick();
  void write(float val_in);
  float read(float val_in);

private:

  float feedback = 0.999, drywet = 0.5, dlvl, wlvl, samplerate;
  AllPassFilter apf1, apf2, apf3, apf4, apf5, apf6;
  DelayLine del;
  BQFilter lpf,hpf;
  Chorus chor;
  float tapc = 0, tap1 = 0, tap2 = 0, tap3 = 0, tap4 = 0, tapd = 0, tapf = 0, tap5 = 0, tap6 = 0;
};
