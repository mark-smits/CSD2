#include <iostream>
#include <string>

class Kauwgom
{
public:
  Kauwgom(std::string smaak, float prijs, int aantal);
  ~Kauwgom();
  void geefEigenschappen();
private:
  std::string smaak;
  float prijs;
  int aantal;
};

Kauwgom::Kauwgom(std::string smaak, float prijs, int aantal)
{
  std::cout << "kauwgom in scope" << '\n';
  this->smaak = smaak;
  this->prijs = prijs;
  this->aantal = aantal;
}

Kauwgom::~Kauwgom()
{
  std::cout << "kauwgom uit scope" << '\n';
}

void Kauwgom::geefEigenschappen()
{
  std::cout << "nog " << aantal << " stukjes kauwgom die smaken naar " << smaak << " gekocht voor " << prijs << '\n';
}

int main()
{
  Kauwgom gompie("aardbei", 1.49, 20);
  gompie.geefEigenschappen();
  return 0;
}
