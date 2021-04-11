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
  Reverb(uint rate);
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

  float feedback = 0.999, drywet = 0, dlvl, wlvl;
  uint samplerate;
  AllPassFilter apf1{samplerate*4.1/1000.0,0.36,samplerate}, apf2{samplerate*8.0/1000.0,0.2,samplerate}, 
  apf3{samplerate*11.7/1000.0,0.41,samplerate}, apf4{samplerate*15.7/1000.0,0.13,samplerate}, 
  apf5{samplerate*61.3/1000.0,0.27,samplerate}, apf6{samplerate*88.9/1000.0,0.58,samplerate};
  DelayLine del{samplerate*200.0/1000.0};
  BQFilter lpf{samplerate},hpf{samplerate};
  Chorus chor{samplerate};
  float tapc = 0, tap1 = 0, tap2 = 0, tap3 = 0, tap4 = 0, tapd = 0, tapf = 0, tap5 = 0, tap6 = 0;
};
