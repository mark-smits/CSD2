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
  if (this->stage == "a")
  {
    this->value += 1 / ( this->samplerate * (this->attack*0.001) );
    if (this->value > 1)
    {
      this->stage = "d";
      this->value = 1;
    }
  } else if (this->stage == "d") {
    this->value -= (1-this->sustain) / ( this->samplerate * (this->decay*0.001) );
    if (this->value < this->sustain)
    {
      this->stage = "s";
      this->value = this->sustain;
    }
  } else if (this->stage == "s") {
    this->value = this->sustain;
  } else if (this->stage == "r") {
    this->value -= this->sustain / ( this->samplerate * (this->release*0.001) );
    if (this->value <= 0) {
      this->stage = "n";
      this->value = 0;
    }
  } else {
    this->value = 0;
  }
}

void Envelope::initialize()
{
  this->value = 0;
  this->stage = "a";
}

void Envelope::releaseStage()
{
  this->stage = "r";
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
  return this->value;
}

std::string Envelope::getStage()
{
  return this->stage;
}

void Envelope::printValue()
{
  std::cout << "Current Envelope Value: " << value << '\n';
}
