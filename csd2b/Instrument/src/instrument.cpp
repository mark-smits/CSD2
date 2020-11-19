#include <iostream>
#include <string>
#include "instrument.h"

Instrument::Instrument(std::string instrumentNaam, std::string instrumentKlank)
{
  naam = instrumentNaam;
  klank = instrumentKlank;
  std::cout << naam << " is in scope \n";
}

Instrument::~Instrument()
{
  std::cout << naam << " is uit scope \n";
}

void Instrument::play()
{
  std::cout << naam << " doet " << klank << "\n";
}
