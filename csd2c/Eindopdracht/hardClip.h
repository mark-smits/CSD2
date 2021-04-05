#ifndef _HARDCLIP_H_
#define _HARDCLIP_H_

#include <iostream>

//Class Initiation
class Hardclip{
//acces specifier
public:
  Hardclip();
  ~Hardclip();
//Calculation
void Hard();
double Clip();

//setters and getters
void setDrive(int drive_in);
int getDrive();

//Catching the inbuf[i]
double Catch(double input);

//Acces specifier
protected:
//variabeles
double sampletje;
double sample;
 int drive;
double input;
};

#endif
