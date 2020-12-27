#include "synthvoice.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "envelope.h"
#include <iostream>

Synthvoice::Synthvoice(float frequency, double samplerate) :
  frequency(frequency), samplerate(samplerate), amplitude(1), saw1(frequency,samplerate)
{
  std::cout << "Synthvoice Constructor" << '\n';
}

Synthvoice::~Synthvoice()
{
  std::cout << "Synthvoice Destructor" << '\n';
}

void Synthvoice::noteOn()
{

}

void Synthvoice::noteOff()
{

}

void Synthvoice::tick()
{
  saw1.tick();
}

void Synthvoice::setAmp(float sawAmp)
{
  saw1.setAmp(sawAmp);
}

void Synthvoice::setFrequency(float frequency)
{
  saw1.setFrequency(frequency);
}

float Synthvoice::getSample()
{
  return saw1.getSample();
}
