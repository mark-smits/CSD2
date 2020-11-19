#include <string>

class Instrument
{
public:
  Instrument(std::string instrumentNaam, std::string instrumentKlank); //construcor
  ~Instrument(); //deconstructor
  void play();
private:
  std::string naam;
  std::string klank;
};
