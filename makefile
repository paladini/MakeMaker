CC=g++
FLAGS=-std=c++11

all: test

test_compile:
	$(CC) src/Run.cpp -o binary/Run $(FLAGS)

test:
	cd binary/ && clear && ./Run g++ test.c test2.c testando -o

compile:
	$(CC) src/Flag.hpp -o binary/Flag.o
	$(CC) src/Compiler.hpp -o binary/Compiler.o
	$(CC) src/File.hpp -o binary/File.o
	$(CC) src/Command.hpp -o binary/Command.o