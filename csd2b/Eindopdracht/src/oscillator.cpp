#include "oscillator.h"
#include <iostream>

Oscillator::Oscillator(float frequency, double samplerate) : frequency(frequency),
  samplerate(samplerate), amplitude(1.0), sample(0), phase(0)
{
  std::cout << "Oscillator Constructor" << '\n';
}

Oscillator::~Oscillator()
{
  std::cout << "Oscillator Destructor" << '\n';
}

void Oscillator::tick()
{
  phase += frequency/samplerate;
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

void Oscillator::setSample(float samp)
{
  this->sample = samp;
}

float Oscillator::getSample()
{
  return sample;
}

float Oscillator::getPhase()
{
  return phase;
}
