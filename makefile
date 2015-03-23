CC=g++
FLAGS=-std=c++11

all: test

test_compile:
	$(CC) src/Run.cpp -o binary/Run

test:
	cd binary/ && clear && clear && ./Run

compile:
	$(CC) src/Flag.hpp -o binary/Flag.o
	$(CC) src/Compiler.hpp -o binary/Compiler.o
	$(CC) src/File.hpp -o binary/File.o
	$(CC) src/Command.hpp -o binary/Command.o