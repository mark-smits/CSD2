#include <string>
#include "instrument.h"

class StringInst: public Instrument
{
public:
  StringInst(std::string instrumentNaam, std::string instrumentKlank, std::string instrumentType, std::string instrumentPR);
  ~StringInst();
  void setDetune(float sawDetune);
  float getDetune();
private:
  float sawDetune;
};
