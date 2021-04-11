#pragma once
#include "delayLine.h"
#include "bqFilter.h"

typedef unsigned int uint;

class AllPassFilter {

public:

  AllPassFilter(uint delTime_in, float g_in, uint samplerate);
  ~AllPassFilter();

  void setG(float g_in);
  float getG();
  void setA(float a_in);
  float getA();
  void setLPF(float freq, float q_val);
  void setDelTime(float val_in);
  
  inline void tick(){ del.tick(); }
  inline void write(float val_in){ del.write( val_in + del.read() * -val_g * val_a ); }
  float read(float val_in);

private:

  uint delTime;
  uint samplerate;
  DelayLine del{delTime*4};
  BQFilter lpf{samplerate}, apf{samplerate}; //additional biquad allpassfilter added for more smearing
  float val_g;
  float val_a = 0.95;
};
