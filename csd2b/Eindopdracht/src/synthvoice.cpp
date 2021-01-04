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
  this->noteActive = false;
}

Synthvoice::~Synthvoice()
{
}

void Synthvoice::noteOn(int midiNote, int midiVel)
{
  setFrequency(440 * pow(2,((float)midiNote-69.0)/12.0));
  setGlobalAmp( pow( 10 , ( ( (float)midiVel / 127.0 * 60.0 ) - 60 ) / 20 ) ); //60 db = * 1000; 20 db = * 10; pow( 10 , ( ( (float)midiVel / 127.0 * 60.0 ) - 60 ) / 20 )
  this->ampEnv.initialize();
  setNoteOn(true);
}

void Synthvoice::noteOff()
{
  this->ampEnv.releaseStage();
  setNoteOn(false);
}

void Synthvoice::tick()
{
  this->sine1.tick();
  this->square1.tick();
  this->saw1.tick();
  this->ampEnv.tick();
}

void Synthvoice::setIndivivualAmp(float sineAmp, float squareAmp, float sawAmp)
{
  this->sine1.setAmp(sineAmp);
  this->square1.setAmp(squareAmp);
  this->saw1.setAmp(sawAmp);
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
  this->frequency = frequency;
  sine1.setFrequency(this->frequency * pow(2.0,(float)this->sinePOffsetST/12.0));
  square1.setFrequency(this->frequency * pow(2.0,(float)this->squarePOffsetST/12.0));
  saw1.setFrequency(this->frequency * pow(2.0,(float)this->sawPOffsetST/12.0));
}

void Synthvoice::setFreqOffset(float sineOffset, float squareOffset, float sawOffset)
{
  this->sinePOffsetST = sineOffset;
  this->squarePOffsetST = squareOffset;
  this->sawPOffsetST = sawOffset;
  setFrequency(this->frequency);
}

float Synthvoice::getSample()
{
  return (this->sine1.getSample()*this->sine1.getAmp() + this->square1.getSample()*this->square1.getAmp() + this->saw1.getSample()*this->saw1.getAmp()) * this->ampEnv.getValue() * this->amplitude;
}

void Synthvoice::setSync(float sync)
{
  this->saw1.setSync(sync);
}

void Synthvoice::setShaper(float value, float dw)
{
  this->sine1.setShaper(value, dw);
}

void Synthvoice::setPW(float pw)
{
  this->square1.setPW(pw);
}

void Synthvoice::setNoteOn(bool note)
{
  this->noteActive = note;
}

bool Synthvoice::getNoteOn()
{
  return this->noteActive;
}

void Synthvoice::setAmpADSR(float att, float dec, float sus, float rel)
{
  this->ampEnv.setADSR(att, dec, sus, rel);
}
