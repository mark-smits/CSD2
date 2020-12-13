#include <string>
#include "instrument.h"

class WoodWindInst: public Instrument
{
public:
  WoodWindInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR);
  ~WoodWindInst();
  void setPWM(float pulseWidthMod);
  float getPWM();
private:
  float pulseWidthMod;
};
