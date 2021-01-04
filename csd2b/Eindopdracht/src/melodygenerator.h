#ifndef _MEL_GEN_H_
#define _MEL_GEN_H_
#include <iostream>

#pragma once

class MelodyGenerator
{
public:
  //constructor and destructor
  MelodyGenerator(int start, int root, int noteSize);
  ~MelodyGenerator();

  //setters & getters
  void setScale(int notes[]);
  void setRoot(int root);
  void setNote(int note);
  int getNote();
private:
  int noteSize;
  int* notes;
  int root;
  int currentnote;
  int noteIndex;
  int octaveIndex;
  int randOption;
};

#endif
