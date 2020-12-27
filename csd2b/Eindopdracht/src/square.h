#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include "oscillator.h"

#pragma once

class Square : public Oscillator
{
public:
  //constructor and destructor
  Square(float frequency, double samplerate);
  ~Square();

  //override the calc function
  void calc();
};

#endif
