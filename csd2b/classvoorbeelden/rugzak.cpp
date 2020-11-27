#include <iostream>
#include <string>

class Rugzak
{
public:
Rugzak(float inhoud, std::string merk, int compartimenten, std::string kleur);
~Rugzak();
void setKleur(std::string nieuweKleur);
std::string getKleur();
void geefEigenschappen();
private:
  float inhoud;
  std::string merk;
  int compartimenten;
  std::string kleur;
};

Rugzak::Rugzak(float inhoud, std::string merk, int compartimenten, std::string kleur)
{
  std::cout << "Rugzak in scope" << '\n';
  this->inhoud = inhoud;
  this->merk = merk;
  this->compartimenten = compartimenten;
  this->kleur = kleur;
}

Rugzak::~Rugzak()
{
  std::cout << "Rugzak uit scope" << '\n';
}

void Rugzak::setKleur(std::string nieuweKleur)
{
  this->kleur = nieuweKleur;
}

std::string Rugzak::getKleur()
{
  return this->kleur;
}

void Rugzak::geefEigenschappen()
{
  std::cout << "Rugzak: " << inhoud << " L  " << merk << " (merk)  " << compartimenten << " vakken  " << kleur << " (kleur) " << '\n';
}

int main()
{
  Rugzak tas(8.2, "Nike", 3, "zwart");
  tas.geefEigenschappen();
  std::cout << tas.getKleur() << '\n';
  tas.setKleur("Rood");
  tas.geefEigenschappen();
  return 0;
}
