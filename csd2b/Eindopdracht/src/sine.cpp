#define _USE_MATH_DEFINES
#include "sine.h"
#include <math.h>

Sine::Sine(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  std::cout << "Sine Constructor" << "\n";
  setShaper(1,0);
}

Sine::~Sine()
{
  std::cout << "Sine Destructor" << "\n";
}

void Sine::calc()
{
  setSample( sin( M_PI * 2 * getPhase() ) );
  if (getSample() > 0)
  {
    while (getSample() > getShaperValue())
    {
      setSample( getSample() - getShaperValue() );
    }
  } else {
    while (getSample() < getShaperValue()*(-1))
    {
      setSample( getSample() + getShaperValue() );
    }
  }
  setSample( getSample() / getShaperValue() );
  //dry wet: 0 = dry; 1 = wet;
  setSample( getSample()*getShaperDW() + sin(M_PI * 2 * getPhase())*(1-getShaperDW()) );
}

void Sine::setShaper(float value, float dw)
{
  this->shaperValue = value;
  this->shaperDW = dw;
}

float Sine::getShaperValue()
{
  return shaperValue;
}

float Sine::getShaperDW()
{
  return shaperDW;
}
