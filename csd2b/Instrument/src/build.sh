#! /bin/bash

g++ -c main.cpp
g++ -c instrument.cpp
g++ -o instrument main.o instrument.o
