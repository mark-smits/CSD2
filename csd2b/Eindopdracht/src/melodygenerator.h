#ifndef _MEL_GEN_H_
#define _MEL_GEN_H_
#include <iostream>

#pragma once

class MelodyGenerator
{
public:
  //constructor and destructor
  MelodyGenerator(int start, int root);
  ~MelodyGenerator();

  //setters & getters
  void setScale(int notes[]);
  void setRoot(int root);
  void setNote(int note);
  int getNote();
private:
  int notes [7];
  int root;
  int currentnote;
  int noteIndex;
  int octaveIndex;
  int randOption;
};

#endif
