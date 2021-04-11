#ifndef _HARDCLIP_H_
#define _HARDCLIP_H_

#include <iostream>

class Hardclip{

public:
  Hardclip();
  ~Hardclip();

  void tick();
  float read();

  void setDrive(int drive_in);
  int getDrive();

  void write(float input);

protected:
  float sample_dry;
  float sample_wet;
  int drive;
  float input;
};

#endif
