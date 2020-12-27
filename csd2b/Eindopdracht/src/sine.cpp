#define _USE_MATH_DEFINES
#include "sine.h"
#include <math.h>

Sine::Sine(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  std::cout << "Sine Constructor" << "\n";
}

Sine::~Sine()
{
  std::cout << "Sine Destructor" << "\n";
}

void Sine::calc()
{
  setSample( sin( M_PI * 2 * getPhase() ) );
}
