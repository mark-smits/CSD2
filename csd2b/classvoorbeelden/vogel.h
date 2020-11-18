// Beschrijving vd class
#include <string>

class Vogel
{
public:
  Vogel(std::string vogelNaam, float vogelSpW, std::string vogelKleur); //construcor
  ~Vogel(); //deconstructor
  void vliegen();
  void geefEigenschappen();
private:
  std::string naam;
  float spanwijdte;
  std::string kleur;
};
