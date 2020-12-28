#include "synthvoice.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "envelope.h"
#include <math.h>
#include <iostream>

Synthvoice::Synthvoice(float frequency, double samplerate) :
  frequency(frequency), samplerate(samplerate), amplitude(1),
  sine1(frequency,samplerate),
  square1(frequency,samplerate),
  saw1(frequency,samplerate),
  ampEnv(100, 500, 0.6, 500, samplerate)
{
  setFreqOffset(0,0,0);
  setIndivivualAmp(1,1,1);
  std::cout << "Synthvoice Constructor" << '\n';
}

Synthvoice::~Synthvoice()
{
  std::cout << "Synthvoice Destructor" << '\n';
}

void Synthvoice::noteOn(int midiNote, int midiVel)
{
  setFrequency(440 * pow(2,(69-midiNote)/12));
  setGlobalAmp( pow( 10 , ( ( (float)midiVel / 127.0 * 60.0 ) - 60 ) / 20 ) ); //60 db = * 1000; 20 db = * 10; pow( 10 , ( ( (float)midiVel / 127.0 * 60.0 ) - 60 ) / 20 )
  ampEnv.initialize();
}

void Synthvoice::noteOff()
{
  ampEnv.releaseStage();
}

void Synthvoice::tick()
{
  sine1.tick();
  square1.tick();
  saw1.tick();
  ampEnv.tick();
}

void Synthvoice::setIndivivualAmp(float sineAmp, float squareAmp, float sawAmp)
{
  sine1.setAmp(sineAmp);
  square1.setAmp(squareAmp);
  saw1.setAmp(sawAmp);
}

void Synthvoice::setGlobalAmp(float amplitude)
{
  if (amplitude > 1.0)
  {
    this->amplitude = 1.0;
  } else {
    this->amplitude = amplitude;
  }
}

void Synthvoice::setFrequency(float frequency)
{
  sine1.setFrequency(frequency * pow(2,sinePOffsetST/12));
  square1.setFrequency(frequency * pow(2,squarePOffsetST/12));
  saw1.setFrequency(frequency * pow(2,sawPOffsetST/12));
}

void Synthvoice::setFreqOffset(float sineOffset, float squareOffset, float sawOffset)
{
  sinePOffsetST = sineOffset;
  squarePOffsetST = squareOffset;
  sawPOffsetST = sawOffset;
  setFrequency(frequency);
}

float Synthvoice::getSample()
{
  return (sine1.getSample() + square1.getSample() + saw1.getSample()) * ampEnv.getValue();
}

void Synthvoice::setSync(float sync)
{
  saw1.setSync(sync);
}

void Synthvoice::setShaper(float value, float dw)
{
  sine1.setShaper(value, dw);
}

void Synthvoice::setPW(float pw)
{
  square1.setPW(pw);
}
