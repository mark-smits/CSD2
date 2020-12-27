#define _USE_MATH_DEFINES
#include "saw.h"
#include <math.h>

Saw::Saw(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  std::cout << "Saw Constructor" << "\n";
}

Saw::~Saw()
{
  std::cout << "Saw Destructor" << "\n";
}

void Saw::calc()
{
  setSample(0);
  for (int n = 1; n < 50; n+=1)
  {
    setSample( getSample() + ( sin( M_PI * 2 * getPhase() * n ) / n ) );
  }
}
