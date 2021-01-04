#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "oscillator.h"
#include "envelope.h"
#include "sandh.h"
#include "synthvoice.h"
#include "melodygenerator.h"
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

#define PI_2 6.28318530717959

int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init("example.exe");
  double samplerate = jack.getSamplerate();

  // user input
  std::fstream scale {"./scale.txt", std::ios::in};
  std::string melNotes {};
  int sizeNootjes;
  int rootNoteOffset;
  bool hasLine = true;
  if(scale.is_open())
  {
    std::getline(scale, melNotes);
    sizeNootjes = std::stoi(melNotes);
    std::getline(scale, melNotes);
    rootNoteOffset = std::stoi(melNotes);
  }
  int nootjes[sizeNootjes];
  if(scale.is_open())
  {
    int i = 0;
    while (hasLine)
    {
      std::getline(scale, melNotes);
      if (melNotes == "end")
      {
        if (i < sizeNootjes)
        {
          std::cout << "error: too little notes in scale.txt in comparison to specified nr of notes" << '\n';
          std::cout << "will fill list with latest note" << '\n';
          while (i < sizeNootjes)
          {
            nootjes[i] = nootjes[i-1];
            i++;
          }
        }
        hasLine = false;
      }
      else if (i >= sizeNootjes)
      {
        std::cout << "error: too many notes in scale.txt in comparison to specified nr of notes" << '\n';
        std::cout << "will ignore further notes" << '\n';
        hasLine = false;
      }
      else
      {
        nootjes[i] = std::stoi(melNotes);
        i++;
      }
    }
  }
  for (unsigned int i = 0; i < sizeof(nootjes)/sizeof(nootjes[0]);i++){
    std::cout << "nootjes " << i << " : " << nootjes[i] << '\n';
  }

  // init melodie
  MelodyGenerator melodie1(36 + nootjes[0] + rootNoteOffset,rootNoteOffset,sizeNootjes);
  MelodyGenerator melodie2(48 + nootjes[0] + rootNoteOffset,rootNoteOffset,sizeNootjes);
  MelodyGenerator melodie3(60 + nootjes[0] + rootNoteOffset,rootNoteOffset,sizeNootjes);
  std::cout << "size of nootjes: " << sizeNootjes << '\n';
  melodie1.setScale( nootjes );
  melodie2.setScale( nootjes );
  melodie3.setScale( nootjes );

  // init synthvoices
  Synthvoice voice1(100, samplerate);
  Synthvoice voice2(100, samplerate);
  Synthvoice voice3(100, samplerate);

  voice1.setIndivivualAmp(1,0,0);
  voice1.setShaper(0.33,1);
  voice1.noteOn(36,63);
  voice1.setAmpADSR(200,1000,0.6,500);

  voice2.setIndivivualAmp(0,1,0);
  voice2.setPW(0.5);
  voice2.noteOn(48,63);
  voice2.setAmpADSR(50,500,0.8,200);

  voice3.setIndivivualAmp(0,0,1);
  voice3.setSync(1);
  voice3.noteOn(60,63);
  voice3.setAmpADSR(5,150,0,100);
  // init sample and hold modules
  SandH sh1(samplerate);
  SandH sh2(samplerate);
  SandH sh3(samplerate);
  sh1.generateTime();
  sh2.generateTime();
  sh3.generateTime();


  // init time functions
  auto millis_0 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

  //assign a function to the JackModule::onProces
  jack.onProcess = [&voice1,&voice2,&voice3,&millis_0,&millis,&samplerate,&sh1,&sh2,&sh3,&melodie1,&melodie2,&melodie3](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    static float amplitude = 0.15;

    millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millis_0;

    // voice 1 note on and off
    if (millis % 5000 < 4500)
    {
      if (!voice1.getNoteOn())
      {
        voice1.noteOn(melodie1.getNote(),63);
      }
    }
    else
    {
      if (voice1.getNoteOn())
      {
        voice1.noteOff();
      }
    }

    // voice 2 note on and off
    if (millis % 2000 < 1800)
    {
      if (!voice2.getNoteOn())
      {
        voice2.noteOn(melodie2.getNote(),63);
      }
    }
    else
    {
      if (voice2.getNoteOn())
      {
        voice2.noteOff();
      }
    }

    // voice 3 note on and off
    if (millis % 100 < 50)
    {
      if (!voice3.getNoteOn())
      {
        voice3.noteOn(melodie3.getNote(),63);
      }
    }
    else
    {
      if (voice3.getNoteOn())
      {
        voice3.noteOff();
      }
    }

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = ( voice1.getSample() + voice2.getSample() + voice3.getSample() ) * amplitude;
      voice1.tick();
      voice2.tick();
      voice3.tick();

      voice1.setShaper( (1/ (1 + ( 5 * sh1.getValue() ) ) ) ,1);
      voice2.setPW(sh2.getValue());
      voice3.setSync(1 + (4 * sh3.getValue()));

      sh1.tick();
      sh2.tick();
      sh3.tick();
    }

    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
    }
  }

  //end the program
  return 0;
} // main()
