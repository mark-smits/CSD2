#include "oscillator.h"
#include <iostream>

Oscillator::Oscillator(float frequency, double samplerate)
{
  this->frequency = frequency;
  this->samplerate = samplerate;
  amplitude = 1.0;
  sample = 0;
  phase = 0;

}

Oscillator::~Oscillator()
{
}

void Oscillator::tick()
{
  while (this->phase > 1)
  {
    this->phase -= 1;
  }
  this->phase += frequency/samplerate;
  calc();
}

void Oscillator::calc()
{

}

void Oscillator::setFrequency(float freq)
{
  this->frequency = freq;
}

float Oscillator::getFrequency()
{
  return frequency;
}

void Oscillator::setAmp(float amp)
{
  this->amplitude = amp;
}

float Oscillator::getAmp()
{
  return this->amplitude;
}

void Oscillator::setSample(float samp)
{
  this->sample = samp;
}

float Oscillator::getSample()
{
  return this->sample;
}

float Oscillator::getPhase()
{
  return this->phase;
}

void Oscillator::setSR(double sr)
{
  this->samplerate = sr;
}
