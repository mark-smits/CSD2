#include "saw.h"
#include <cmath>

Saw::Saw(float freq, float rate) : samplerate(rate), frequency(freq)
{}

Saw::~Saw()
{}


void Saw::setFrequency()
{
  std::cout << "Osc speed\n";
  std::cin >> frequency;
}

float Saw::getFrequency()
{
  return frequency;
}

float Saw::getSample()
{
  return sample;
}

void Saw::tick()
{
  //This calculation was given to me by Bas Maat
  phase += frequency / samplerate;
  while(phase >= 1.0) phase = phase - 1.0;
  sample = phase;
}
