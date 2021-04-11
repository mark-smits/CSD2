#pragma once

#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include "chorus.h"
#include "effect.h"
#include <cstring>
#include <iostream>

typedef unsigned int uint;

class Reverb : public Effect {

public:

  Reverb(uint rate);
  ~Reverb();

  inline void setFB(float fb_in){ feedback = fb_in; }
  inline float getFB(){ return feedback; }
  void setdw(float val_in);
  void setTone(float val_in);
  void setSize(float val_in);

  void tick();
  void write(float val_in);
  float read(float val_in);

private:

  float feedback = 0.95, drywet = 0.0, drywet_exponent = 0.65, dlvl, wlvl;
  AllPassFilter apf1{getSamplerate()*4.1/1000.0,0.36,getSamplerate()}, apf2{getSamplerate()*8.0/1000.0,0.2,getSamplerate()}, 
  apf3{getSamplerate()*11.7/1000.0,0.41,getSamplerate()}, apf4{getSamplerate()*15.7/1000.0,0.13,getSamplerate()}, 
  apf5{getSamplerate()*61.3/1000.0,0.27,getSamplerate()}, apf6{getSamplerate()*88.9/1000.0,0.58,getSamplerate()};
  DelayLine del{getSamplerate()*200.0/1000.0};
  BQFilter lpf{getSamplerate()},hpf{getSamplerate()};
  Chorus chor{getSamplerate()};
  float tapc = 0.0, tap1 = 0.0, tap2 = 0.0, tap3 = 0.0, tap4 = 0.0, tapd = 0.0, tapf = 0.0, tap5 = 0.0, tap6 = 0.0;
  float early_reflections_amp = 0.4, late_reflections_amp = 0.3; 
  float wet_output = 0.0;
  float samplerateMillisec = getSamplerate()/1000.0;
  float apf1_default_delay_time_ms = 4.1;
  float apf2_default_delay_time_ms = 8.0;
  float apf3_default_delay_time_ms = 11.7;
  float apf4_default_delay_time_ms = 15.7;
  float apf5_default_delay_time_ms = 61.3;
  float apf6_default_delay_time_ms = 88.9;
  float delay_mult = 1.0;
  float lpf_freq = 3000.0;
  float hpf_freq = 100.0;
  float apf1_freq = 4814.0;
  float apf2_freq = 6065.0;
  float apf3_freq = 3178.0;
  float apf4_freq = 3789.0;
  float apf5_freq = 2313.0;
  float apf6_freq = 2108.0;
  float resonance = 0.707;
};
