#define _USE_MATH_DEFINES
#include "square.h"
#include <math.h>

Square::Square(float frequency, double samplerate) : Oscillator(frequency, samplerate)
{
  std::cout << "Square Constructor" << "\n";
  setPW(0.5);
}

Square::~Square()
{
  std::cout << "Square Destructor" << "\n";
}

void Square::calc()
{
  setSample(0);
  for (int n = 1; n < 20; n++)
  {
    setSample( getSample() + ( sin(M_PI * getPW() * n) * cos( M_PI * 2 * getPhase() * n ) / n * 2) );
  }
}

void Square::setPW(float pw)
{
  this->pw = pw;
}

float Square::getPW()
{
  return this->pw;
}
