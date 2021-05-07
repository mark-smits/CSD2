CXX = g++
CXXFLAGS = -I/usr/local/include -Wall -std=c++17
LDFLAGS= -ljack -lwiringPi

all: example

example : jack_module.o delayLine.o button.o encoder.o looper.o main.o
	$(CXX) -o $@ $(CFLAGS) jack_module.o delayLine.o button.o encoder.o looper.o main.o $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm -f *.o
	rm -f example
