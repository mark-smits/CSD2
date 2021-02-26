#pragma once

typedef unsigned int uint;

class BQFilter {

public:

  // constructor & destructor
  BQFilter(uint samplerate);
  BQFilter(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in, uint samplerate);
  ~BQFilter();

  // setters & getters
  void setParameters(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in);

  // setters for specific types of filters
  void setLPF(float freq, float q_val);
  void setHPF(float freq, float q_val);
  void setBPF(float freq, float q_val);
  void setBRF(float freq, float q_val);
  void setAPF(float freq, float q_val);

  // filter functions
  void write(float val_in);
  float read();

  // log functions
  void printvals();

private:

  float a0, a1, a2, b1, b2, xn, xn1, xn2, yn, yn1, yn2;
  uint samplerate;

};
