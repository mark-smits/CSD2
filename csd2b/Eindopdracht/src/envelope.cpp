#include "envelope.h"
#include <iostream>

Envelope::Envelope(float attack, float decay, float sustain, float release, double samplerate) :
  attack(attack), decay(decay), sustain(sustain), release(release), samplerate(samplerate), value(0), stage("a")
{
  std::cout << "Envelope Constructor" << '\n';
}

Envelope::~Envelope()
{
  std::cout << "Envelope Destructor" << '\n';
}

void Envelope::tick()
{
  if (stage == "a")
  {
    value += 1 / ( samplerate * (attack*0.001) );
    if (value > 1)
    {
      stage = "d";
      value = 1;
    }
  } else if (stage == "d") {
    value -= (1-sustain) / ( samplerate * (decay*0.001) );
    if (value < sustain)
    {
      stage = "s";
      value = sustain;
    }
  } else if (stage == "s") {
    value = sustain;
  } else if (stage == "r") {
    value -= sustain / ( samplerate * (release*0.001) );
    if (value < 0) {
      stage = "n";
      value = 0;
    }
  } else {
    value = 0;
  }
}

void Envelope::initialize()
{
  this->value = 0;
  stage = "a";
}

void Envelope::releaseStage()
{
  stage = "r";
}

void Envelope::setADSR(float attack, float decay, float sustain, float release)
{
  this->attack = attack;
  this->decay = decay;
  this->sustain = sustain;
  this->release = release;
}

float Envelope::getValue()
{
  return value;
}
