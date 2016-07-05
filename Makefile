# Makefile for the Grainfuck program

grainfuck: grainfuck.o
	g++ -std=c++11 grainfuck.o -o grainfuck -lsfml-graphics -lsfml-window -lsfml-system

grainfuck.o: main.cpp main.hpp errorCodes.hpp
	g++ -std=c++11 -c main.cpp -o grainfuck.o


.PHONY clean:
	rm *.o
	rm ./grainfuck
