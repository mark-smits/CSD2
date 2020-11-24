#include <iostream>
#include <string>

class Waterfles {
public:
  Waterfles(float volume, std::string inhoud);
  ~Waterfles();
  void setVol(float volume);
  float getVol();
  void setInhoud(std::string inhoud);
  std::string getInhoud();
  void drinken();
  void geefInhoud();
private:
  float volume;
  std::string inhoud;
};

Waterfles::Waterfles(float volume, std::string inhoud)
{
  std::cout << "Waterfles class in scope" << '\n';
  this->volume = volume;
  this->inhoud = inhoud;
}

Waterfles::~Waterfles()
{
  std::cout << "Waterfles class uit scope" << '\n';
}

void Waterfles::setVol(float volume)
{
  this->volume = volume;
}

float Waterfles::getVol()
{
  return volume;
}

void Waterfles::setInhoud(std::string inhoud)
{
  this->inhoud = inhoud;
}

std::string Waterfles::getInhoud()
{
  return inhoud;
}

void Waterfles::drinken()
{
  std::cout << "slok" << '\n';
}

void Waterfles::geefInhoud()
{
  std::cout << "Fles is gevuld met " << volume << " liter " << inhoud << '\n';
}

int main()
{
  Waterfles fles1(0.75,"koffie");
  fles1.drinken();
  fles1.geefInhoud();
  fles1.setVol(0.5);
  fles1.setInhoud("water");
  fles1.geefInhoud();
  return 0;
}
