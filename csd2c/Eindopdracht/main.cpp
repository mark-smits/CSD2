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
	Encoder encList[5] = {enc1, enc2, enc3, enc4, enc5};
	int lastEncValList[5] = {0,0,0,0,0};
	
	int index = 0;
	
	JackModule jack;
	
	jack.init(argv[0]);
	float samplerate = jack.getSamplerate();
	
	Reverb verb(samplerate);
	TapeShifter shifter(samplerate*2);
	Hardclip clipper;
	clipper.setDrive(2);
	
	jack.onProcess = [&verb, &shifter, &clipper, &index, &encList, &lastEncValList](jack_default_audio_sample_t *inBuf,
		jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {
			
		index++;
		
		for (int i = 0; i < 5; i++)
		{
			encList[i].tick();
		}
		
		while (index > 10) {
			index -= 10;
		
			for (int i = 0; i < 5; i++)
			{
				int currentVal = encList[i].getVal();
				
				if (currentVal != lastEncValList[i])
				{
					std::cout << "\nEncoder " << i+1 << ": " << currentVal << "\n";
					lastEncValList[i] = currentVal;
					switch(i)
					{
						case 0:
							verb.setFB( pow( 0.01, ( 1.0 / (5.0*currentVal+1) ) ) );
							std::cout << "\nReverb feedback now at value: " << verb.getFB() << "\n";
							break;
						case 1:
							verb.setdw(currentVal/10.0);
							std::cout << "\nReverb dry/wet level set to: " << currentVal/10.0 << "\n";
							break;
						case 2:
							verb.setTone(currentVal);
							std::cout << "\nReverb tone set to: " << currentVal*10.0 << "%\n";
							break;
						case 3:
							//verb.setSize(currentVal);
							//std::cout << "\nReverb size set to: " << currentVal*10.0 << "%\n";
							std::cout << "\n4 changed\n";
							break;
						case 4:
							std::cout << "\n5 changed\n";
							break;
					}
				}
			}
		}
		
		for(unsigned int i = 0; i < nframes; i++) {
			shifter.signalToBeShifted( inBuf[i] );
			verb.write( shifter.pitchshiftedSignal() );
			clipper.Catch( verb.read( shifter.pitchshiftedSignal() ) );
			verb.tick();
			shifter.tick();
			clipper.Hard();
			outBuf[i] = clipper.Clip() * 1.0;
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
			case 'c':
				shifter.changeSawFrequency();
				break;
		}
	}
	
	return 0;
}
