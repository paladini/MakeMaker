CC=g++

all: compile_and_test

compile_and_test:
	g++ src/Flag.hpp -o binary/Flag.o
	g++ src/Compiler.hpp -o binary/Compiler.o
	g++ src/File.hpp -o binary/File.o
	g++ src/Command.hpp -o binary/Command.o
	
