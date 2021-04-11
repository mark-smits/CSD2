#pragma once

#include "effect.h"

typedef unsigned int uint;

class BQFilter : public Effect {

public:

  BQFilter(uint rate);
  BQFilter(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in, uint rate);
  ~BQFilter();

  void setParameters(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in);

  void setLPF(float freq, float q_val);
  void setHPF(float freq, float q_val);
  void setBPF(float freq, float q_val);
  void setBRF(float freq, float q_val);
  void setAPF(float freq, float q_val);

  void write(float val_in);
  float read();

  void printVals();

private:

  float a0, a1, a2, b1, b2, xn = 0, xn1 = 0, xn2 = 0, yn = 0, yn1 = 0, yn2 = 0;
};
