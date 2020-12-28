#ifndef _SAW_H_
#define _SAW_H_
#include <iostream>
#include "oscillator.h"

#pragma once

class Saw : public Oscillator
{
public:
  //constructor and destructor
  Saw(float frequency, double samplerate);
  ~Saw();

  //override the calc function
  void calc();
  //setters & getters
  void setSync(float sync);
  float getSync();
private:
  float syncValue;
};

#endif
