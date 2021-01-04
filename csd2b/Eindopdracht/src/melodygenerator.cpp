#include "melodygenerator.h"
#include <random>
#include <functional>
#include <iostream>

std::default_random_engine generatornote;
std::uniform_int_distribution<int> distributionnote(0,4);
auto randnotegen = std::bind( distributionnote, generatornote );

MelodyGenerator::MelodyGenerator(int start, int root, int size)
{
  this->currentnote = start;
  this->root = root;
  this->noteSize = size;
  this->notes = new int[size];
}

MelodyGenerator::~MelodyGenerator()
{
}

void MelodyGenerator::setScale(int notes[])
{
  for (int n = 0; n<noteSize; n++){
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
      this->noteIndex = noteSize - 1;
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

    if (this->noteIndex < noteSize - 1)
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
