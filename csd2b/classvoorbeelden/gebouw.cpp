#include <iostream>
#include <string>

class Gebouw
{
public:
Gebouw(int verdiepingen, float oppervlakte, float prijs, std::string naam);
~Gebouw();
void setPrijs(float prijs);
float getPrijs();
void geefEigenschappen();
private:
  int verdiepingen;
  float oppervlakte;
  float prijs;
  std::string naam;
};

Gebouw::Gebouw(int verdiepingen, float oppervlakte, float prijs, std::string naam)
{
  std::cout << "Constructor aangeroepen, class in scope" << '\n';
  this->verdiepingen = verdiepingen;
  this->oppervlakte = oppervlakte;
  this->prijs = prijs;
  this->naam = naam;
}

Gebouw::~Gebouw()
{
  std::cout << "Destructor aangeroepen, class gaat uit scope" << '\n';
  std::cout << "Gebouw word gesloopt" << '\n';
}

void Gebouw::setPrijs(float prijs)
{
  this->prijs = prijs;
}

float Gebouw::getPrijs()
{
  return this->prijs;
}

void Gebouw::geefEigenschappen()
{
  std::cout << "Gebouw " << naam << " heeft: " << '\n';
  std::cout << verdiepingen << " verdiepingen" << '\n';
  std::cout << oppervlakte << " m^2 oppervlakte" << '\n';
  std::cout << prijs << " euros huurkosten" << '\n';
}

int main()
{
  Gebouw pandje(3, 200, 400, "pandje");
  std::cout << pandje.getPrijs() << '\n';
  pandje.setPrijs(550);
  pandje.geefEigenschappen();
  return 0;
}
