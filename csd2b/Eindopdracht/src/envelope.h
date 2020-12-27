#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_
#include <iostream>

#pragma once

class Envelope {
public:
  //constructor & destructor
  Envelope(float attack, float decay, float sustain, float release, double samplerate);
  ~Envelope();
  //calulations and incrementation
  void tick();
  void initialize();
  void releaseStage();
  //setters & getters
  void setADSR(float attack, float decay, float sustain, float release);
  float getValue();
private:
  float attack;
  float decay;
  float sustain;
  float release;
  double samplerate;
  float value;
  std::string stage;
};

#endif
