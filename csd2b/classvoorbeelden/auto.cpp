// Implementatie vd class

#include <iostream>
#include <string>
#include "auto.h"

Auto::Auto(int jaartalIn, float lengteIn, std::string naamIn)
{
  std::cout << "Auto class in scope" << std::endl;
  jaartal = jaartalIn;
  lengte = lengteIn;
  naam = naamIn;
}

Auto::~Auto()
{
  std::cout << "Auto class uit scope" << std::endl;
}

void Auto::geefEigenschappen()
{
  std::cout << "Jaartal: " << jaartal << std::endl;
  std::cout << "Lengte: " << lengte << std::endl;
  std::cout << "Naam: " << naam << std::endl;
}
