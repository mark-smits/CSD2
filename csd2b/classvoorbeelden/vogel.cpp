// Implementatie vd class

#include <iostream>
#include <string>
#include "vogel.h"

Vogel::Vogel(std::string vogelNaam, float vogelSpW, std::string vogelKleur)
{
  std::cout << "Vogel class in scope" << std::endl;
  naam = vogelNaam;
  spanwijdte = vogelSpW;
  kleur = vogelKleur;
}

Vogel::~Vogel()
{
  std::cout << "Vogel class uit scope" << std::endl;
}

void Vogel::vliegen()
{
  std::cout << "Hihi ik vlieg" << std::endl;
}

void Vogel::geefEigenschappen()
{
  std::cout << "Naam: " << naam << std::endl;
  std::cout << "Spanwijdte: " << spanwijdte << std::endl;
  std::cout << "Kleur: " << kleur << std::endl;
}
