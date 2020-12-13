#include <iostream>
#include <string>
#include "brassInst.h"

BrassInst::BrassInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR) : Instrument(instrumentNaam, instrumentKlank, instrumentType, instrumentPR)
{

}

BrassInst::~BrassInst()
{

}

void BrassInst::setFA(float filterAttackTime)
{
  this->filterAttackTime = filterAttackTime;
}

float BrassInst::getFA()
{
  return filterAttackTime;
}
