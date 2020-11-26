#include <iostream>
#include <string>

class Laptop
{
public:
  Laptop(float schermdiameter, std::string merk, float gewicht, float prijs, float opslag);
  ~Laptop();
  void geefEigenschappen();
private:
  float schermdiameter;
  std::string merk;
  float gewicht;
  float prijs;
  float opslag;
};

Laptop::Laptop(float schermdiameter, std::string merk, float gewicht, float prijs, float opslag)
{
  this->schermdiameter = schermdiameter;
  this->merk = merk;
  this->gewicht = gewicht;
  this->prijs = prijs;
  this->opslag = opslag;
}

Laptop::~Laptop()
{

}

void Laptop::geefEigenschappen()
{
  std::cout << "schermdiameter: " << schermdiameter << '\n';
  std::cout << "merk: " << merk << '\n';
  std::cout << "gewicht: " << gewicht << '\n';
  std::cout << "prijs: " << prijs << '\n';
  std::cout << "opslag: " << opslag << '\n';
}

int main()
{
  Laptop lappie(15.0, "Lenovo", 2.3, 1499.99, 250);
  lappie.geefEigenschappen();

  return 0;
}
