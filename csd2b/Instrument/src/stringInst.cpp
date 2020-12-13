#include <iostream>
#include <string>
#include "stringInst.h"

StringInst::StringInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR) : Instrument(instrumentNaam, instrumentKlank, instrumentType, instrumentPR)
{

}

StringInst::~StringInst()
{

}

void StringInst::setDetune(float sawDetune)
{
  this->sawDetune = sawDetune;
}

float StringInst::getDetune()
{
  return sawDetune;
}
