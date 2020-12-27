#define _USE_MATH_DEFINES
#include "square.h"
#include <math.h>

Square::Square(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  std::cout << "Square Constructor" << "\n";
}

Square::~Square()
{
  std::cout << "Square Destructor" << "\n";
}

void Square::calc()
{
  setSample(0);
  for (int n = 1; n < 50; n+=2)
  {
    setSample( getSample() + ( sin( M_PI * 2 * getPhase() * n ) / n ) );
  }
}
