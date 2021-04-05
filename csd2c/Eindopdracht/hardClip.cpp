#include "hardClip.h"


//Class Initiation
Hardclip::Hardclip()
{
//  this->drive = drive;
}
Hardclip::~Hardclip()
{}
//HardClip
void Hardclip::Hard()
{
  drive = std::max(drive, 0); //Protection against negative numbers
  float x1 = sampletje * drive;

    if(x1 > 1){
      sample = 1;
    }else if(x1 < -1){
      sample = -1;
    }else{
      sample = x1;
    }

}

double Hardclip::Clip()
{
  return sample;
}
//Catch functie
double Hardclip::Catch(double input)
{
  sampletje = input;
  return sampletje;
}
//setters getters
void Hardclip::setDrive(int drive_in)
{
  this->drive = drive_in;
}

int Hardclip::getDrive()
{
  return drive;
}
