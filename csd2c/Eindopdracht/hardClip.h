#ifndef _HARDCLIP_H_
#define _HARDCLIP_H_

#include <iostream>
#include "effect.h"

class Hardclip : public Effect {

public:
  Hardclip();
  ~Hardclip();

  void tick();
  float read();

  void setDrive(float drive_in);
  int getDrive();

  void write(float input);

protected:
  float sample_dry;
  float sample_wet;
  float drive = 1;
  float input;
};

#endif
