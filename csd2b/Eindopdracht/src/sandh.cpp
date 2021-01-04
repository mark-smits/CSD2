#include "sandh.h"
#include <random>
#include <functional>
#include <iostream>

#ifndef _RANDGEN_
#define _RANDGEN_

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,100);
auto randgen = std::bind( distribution, generator );

#endif

SandH::SandH(double samplerate) : samplerate(samplerate)
{
  this->start = 0.8;
  this->value = start;
  this->target = 0.5;
  this->time = 100.0;
  this->rising = false;
  setTimeRange(300,800); //start off at 500-2500 ms
}

SandH::~SandH()
{
}

void SandH::tick()
{
  value += (target - start) / (samplerate / 1000 * time);
  if (rising && value > target)
  {
    this->value = target;
    this->start = target;
    generateTarget();
    generateTime();
  }
  else if (!rising && value < target)
  {
    this->value = target;
    this->start = target;
    generateTarget();
    generateTime();
  }
}

void SandH::generateTarget()
{
  this->target = ( (float)randomGen() ) / 100.0; //generate value between 0 and 1
  if (target > start)
  {
    this->rising = true;
  }
  else
  {
    this->rising = false;
  }
}

void SandH::generateTime()
{
  this->time = ( ( (float)randomGen() ) / 100.0 ) * (this->timeMax - this->timeMin) + this->timeMin;
}

float SandH::getValue()
{
  return value;
}

void SandH::setTimeRange(float timeMin, float timeMax)
{
  this->timeMin = timeMin;
  this->timeMax = timeMax;
}

void SandH::printValues()
{
  std::cout << "value: " << value << '\n';
  std::cout << "target: " << target << '\n';
  std::cout << "start: " << start << '\n';
  std::cout << "time: " << time << '\n';
}

int SandH::randomGen()
{
  return randgen();
}
