#include <iostream>
#include <string>
#include "woodwindInst.h"

WoodWindInst::WoodWindInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR) : Instrument(instrumentNaam, instrumentKlank, instrumentType, instrumentPR)
{

}

WoodWindInst::~WoodWindInst()
{

}

void WoodWindInst::setPWM(float pulseWidthMod)
{
  this->pulseWidthMod = pulseWidthMod;
}

float WoodWindInst::getPWM()
{
  return pulseWidthMod;
}
