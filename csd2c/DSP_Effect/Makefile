CXX = g++
CXXFLAGS = -Ic:/Program\ Files/JACK2/include -Wall -std=c++1z
LDFLAGS= -Lc:/Program\ Files/JACK2/lib32 -llibjack

all: example

example : jack_module.o delayLine.o bqFilter.o chorus.o allPassFilter.o reverb.o main.o
	$(CXX) -o $@ $(CFLAGS) jack_module.o delayLine.o bqFilter.o chorus.o allPassFilter.o reverb.o main.o $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -f *.o
	rm -f example
