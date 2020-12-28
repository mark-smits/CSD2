#ifndef _SH_H_
#define _SH_H
#include <stdlib.h>
#include <random>

#pragma once

class SandH
{
public:
  //constructor and destructor
  SandH(double samplerate);
  ~SandH();
  //calculations and incrementations
  void tick();
  //setters & getters
  void generateTarget();
  void generateTime();
  float getValue();
  void setTimeRange(float timeMin, float timeMax);
  void printValues();
  int randomGen();
private:
  double samplerate;
  float value;
  float target;
  float start;
  //time parameters in milliseconds
  float timeMin;
  float timeMax;
  float time;
  bool rising;
};

#endif
