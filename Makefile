GCC_OPTIONS=-Wall -pedantic -I include 
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


all: 
	g++ assignment2_Part1.cpp Common/InitShader.o -lGLEW -lGL -lglut -o assignment2_Part1
	g++ assignment2_Part2.cpp Common/InitShader.o -lGLEW -lGL -lglut -o assignment2_Part2

