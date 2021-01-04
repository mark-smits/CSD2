#define _USE_MATH_DEFINES
#include "saw.h"
#include <math.h>

Saw::Saw(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  setSync(1);
}

Saw::~Saw()
{
}

void Saw::calc()
{
  setSample(0);
  for (int n = 1; n < 20; n+=1)
  {
    setSample( getSample() + ( sin( M_PI * 2 * getSync() * getPhase() * n ) / n ) );
  }
}

void Saw::setSync(float sync)
{
  this->syncValue = sync;
}

float Saw::getSync()
{
  return this->syncValue;
}
