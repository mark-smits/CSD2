#include "saw.h"
#include <cmath>
//constructor destructor
Saw::Saw(double frequency, double samplerate)
{
  this->samplerate = samplerate;
  this->frequency = frequency;
}

Saw::~Saw()
{}

//Methods
//Ignoring protection for now
void Saw::setFrequency()
{
  std::cout << "Osc speed\n";
  std::cin >> frequency;
  this->frequency = frequency;
}

double Saw::getFrequency()
{
  return frequency;
}
//getSample and tick
double Saw::getSample()
{
  return sampletje;
}

void Saw::tick()
{
  //This calculation was given to me by Bas Maat
  phase += frequency / samplerate;
  // wrap phase from 0 to 1
  if(phase >= 1) phase = phase - 1;
  //Scaling now done elsewhere
  sampletje = phase;
}
