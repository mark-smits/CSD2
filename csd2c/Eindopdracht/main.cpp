#include <thread>
#include "jack_module.h"
#include "math.h"
#include "delayLine.h"
#include "allPassFilter.h"
#include "reverb.h"
#include "bqFilter.h"
#include "chorus.h"
#include "encoder.h"
#include "tapeShifter.h"
#include "hardClip.h"
#include <iostream>
#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char **argv) {
	wiringPiSetup();
	
	Encoder enc1(6, 13), enc2(1, 0), enc3(8, 7), enc4(16, 9), enc5(3, 15);
	enc1.setVal(5);
	enc4.setVal(5);
	Encoder encList[5] = {enc1, enc2, enc3, enc4, enc5};
	int lastEncValList[5] = {5,0,0,5,0};
	
	int index = 0;
	
	JackModule jack;
	
	jack.init(argv[0]);
	float samplerate = jack.getSamplerate();
	
	Reverb verb(samplerate);
	TapeShifter shifter(samplerate*2, samplerate);
	Hardclip clipper;
	clipper.setDrive(1.0);
	
	jack.onProcess = [&verb, &shifter, &clipper, &index, &encList, &lastEncValList](jack_default_audio_sample_t *inBuf,
		jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {
			
		index++;
		
		for (int i = 0; i < 5; i++)
		{
			encList[i].checkPins();
		}
		
		while (index > 10) {
			index -= 10;
		
			for (int i = 0; i < 5; i++)
			{
				int currentVal = encList[i].getVal();
				
				if (currentVal != lastEncValList[i])
				{
					lastEncValList[i] = currentVal;
					switch(i)
					{
						case 0:
							verb.setdw(currentVal/10.0);
							std::cout << "\nReverb dry/wet level set to: " << currentVal/10.0 << "\n";
							break;
						case 1:
							verb.setFB( pow( 0.01, ( 1.0 / (5.0*currentVal+1) ) ) );
							std::cout << "\nReverb feedback now at value: " << verb.getFB() << "\n";
							break;
						case 2:
							verb.setSize(currentVal);
							std::cout << "\nReverb size set to: " << currentVal*10.0 << "%\n";
							break;
						case 3:
							shifter.changeSawFrequency( pow( 10, (currentVal-5.0)/5.0 ) );
							std::cout << "\nPitch shifting set to: " << currentVal*10.0 << "%\n";
							break;
						case 4:
							clipper.setDrive( 1.0 + currentVal/1.5 );
							std::cout << "\nDrive set to: " << 1.0 + currentVal/10.0 <<"\n";
							break;
					}
				}
			}
		}
		
		for(unsigned int i = 0; i < nframes; i++) {
			shifter.write( inBuf[i] );
			verb.write( shifter.read() );
			clipper.write( verb.read( shifter.read() ) );
			verb.tick();
			shifter.tick();
			clipper.tick();
			outBuf[i] = clipper.read() * 1.0;
		}
		return 0;
	};
	
	jack.autoConnect();
	
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
	
	return 0;
}
