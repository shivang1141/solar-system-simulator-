CC=g++
CFLAGS=-pedantic -g -std=c++0x -Wall #-Werror
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

default: NBody

NBody: main.o NBody.o
	$(CC) $(CFLAGS) NBody.o main.o -o NBody $(LFLAGS)
NBody.o : NBody.cpp NBody.hpp
	$(CC) $(CFLAGS) -c NBody.cpp
main.o: main.cpp NBody.hpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm NBody *.o
