CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++17
LDFLAGS = -ljack -lwiringPi

all:example

example : encoder.o delayLine.o bqFilter.o allPassFilter.o chorus.o reverb.o jack_module.o saw.o tapeShifter.o main.o
	$(CC) -o $@ $(CFLAGS) encoder.o delayLine.o bqFilter.o allPassFilter.o chorus.o reverb.o jack_module.o saw.o tapeShifter.o main.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
