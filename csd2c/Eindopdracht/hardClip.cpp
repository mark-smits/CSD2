#include "hardClip.h"

Hardclip::Hardclip()
{

}
Hardclip::~Hardclip()
{
  
}

void Hardclip::tick()
{
  drive = std::max(drive, 0); //Protection against negative numbers
  float x1 = sample_dry * drive;

  if(x1 > 1){
    sample_wet = 1;
  }else if(x1 < -1){
    sample_wet = -1;
  }else{
    sample_wet = x1;
  }

}

float Hardclip::read()
{
  return sample_wet;
}

void Hardclip::write(float input)
{
  sample_dry = input;
}

void Hardclip::setDrive(int drive_in)
{
  this->drive = drive_in;
}

int Hardclip::getDrive()
{
  return drive;
}
