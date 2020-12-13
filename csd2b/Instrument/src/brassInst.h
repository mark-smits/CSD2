#include <string>
#include "instrument.h"

class BrassInst: public Instrument
{
public:
  BrassInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR);
  ~BrassInst();
  void setFA(float filterAttackTime);
  float getFA();
private:
  float filterAttackTime;
};
