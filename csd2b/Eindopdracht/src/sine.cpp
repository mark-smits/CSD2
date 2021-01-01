#define _USE_MATH_DEFINES
#include "sine.h"
#include <math.h>
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) ) //sign functie van: https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c

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
  while (getSample()*sign(getSample()) > getShaperValue())
  {
    setSample( (getSample() * sign(getSample()) - getShaperValue()) * sign(getSample()) );
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
  return this->shaperValue;
}

float Sine::getShaperDW()
{
  return this->shaperDW;
}
