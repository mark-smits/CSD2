#ifndef _SYNTHVOICE_H_
#define _SYNTHVOICE_H_
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "envelope.h"
#include <iostream>

#pragma once

class Synthvoice {
public:
  //constructor & destructor
  Synthvoice(float frequency, double samplerate);
  ~Synthvoice();
  //calculations & incrementation
  void noteOn();
  void noteOff();
  void tick();
  //setters & getters
  void setFrequency(float frequency);
  void setAmp(float sawAmp);
  float getSample();
private:
  double samplerate;
  float frequency;
  float amplitude;
  float sinePOffsetCents;
  float sawPOffsetCents;
  float squarePOffsetCents;
  float sineAmp;
  float sawAmp;
  float squareAmp;
  Saw saw1;
};

#endif
