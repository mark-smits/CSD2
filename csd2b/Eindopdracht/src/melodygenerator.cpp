#include "melodygenerator.h"
#include <random>
#include <functional>
#include <iostream>

std::default_random_engine generatornote;
std::uniform_int_distribution<int> distributionnote(0,4);
auto randnotegen = std::bind( distributionnote, generatornote );

MelodyGenerator::MelodyGenerator(int start, int root)
{
  std::cout << "MelodyGenerator Constructor" << "\n";
  this->currentnote = start;
  this->root = root;
}

MelodyGenerator::~MelodyGenerator()
{
  std::cout << "MelodyGenerator Destructor" << "\n";
}

void MelodyGenerator::setScale(int notes[])
{
  for (int n = 0; n<7; n++){
    this->notes[n] = notes[n];
  }
}

void MelodyGenerator::setRoot(int root)
{
  this->root = this->root;
}

void MelodyGenerator::setNote(int note)
{
  this->currentnote = note;
}

int MelodyGenerator::getNote()
{
  this->octaveIndex = 0;
  this->noteIndex = 0;
  this->randOption = randnotegen();

  this->currentnote -= this->root;
  while (this->currentnote >= 12)
  {
    this->octaveIndex++;
    this->currentnote -= 12;
  }

  while (this->currentnote != this->notes[this->noteIndex])
  {
    this->noteIndex++;
  }

  if (this->randOption <= 1) //stapje omlaag
  {

    if (this->noteIndex > 0)
    {
      this->noteIndex -= 1;
    }
    else
    {
      this->noteIndex = 6;
      if (this->octaveIndex > 0)
      {
        this->octaveIndex -= 1;
      }
    }

  }
  else if (this->randOption == 2) //zelfde noot
  {

  }
  else if (this->randOption >= 3) //stapje omhoog
  {

    if (this->noteIndex < 6)
    {
      this->noteIndex += 1;
    }
    else
    {
      this->noteIndex = 0;
      if (this->octaveIndex < 8)
      {
        this->octaveIndex += 1;
      }
    }

  }
  else
  {

    std::cout << "Error in generating a note" << '\n';

  }
  this->currentnote = this->notes[this->noteIndex] + (this->octaveIndex * 12) + this->root;
  return this->currentnote;
}
