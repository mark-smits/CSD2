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
  void noteOn(int midiNote, int midiVel);
  void noteOff();
  void tick();
  //setters & getters
  void setFrequency(float frequency);
  void setFreqOffset(float sineOffset, float squareOffset, float sawOffset);
  void setIndivivualAmp(float sineAmp, float squareAmp, float sawAmp);
  void setGlobalAmp(float amplitude);
  float getSample();
  bool getNoteOn();
  void setNoteOn(bool note);
  //oscillator specific setters & getters
  void setSync(float sync);
  void setShaper(float value, float dw);
  void setPW(float pw);
  void setAmpADSR(float att, float dec, float sus, float rel);
private:
  double samplerate;
  float frequency;
  float amplitude;
  float sinePOffsetST;
  float sawPOffsetST;
  float squarePOffsetST;
  float sineAmp;
  float sawAmp;
  float squareAmp;
  Saw saw1;
  Sine sine1;
  Square square1;
  Envelope ampEnv;
  bool noteActive;
};

#endif
