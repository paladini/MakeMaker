CC=g++
FLAGS=-std=c++11 -fpermissive -Wformat-security

all: clean test_compile test

test_compile:
	$(CC) src/Test.cpp -o binary/Test $(FLAGS)

test:
	cd binary/ && clear && clear && ./Test compiler g++ main.c -o main

compile:
	$(CC) src/Flag.hpp -o binary/Flag.o
	$(CC) src/Compiler.hpp -o binary/Compiler.o
	$(CC) src/File.hpp -o binary/File.o
	$(CC) src/Command.hpp -o binary/Command.o
	$(CC) src/MakeFile.hpp -o binary/MakeFile.o

clean:
	rm -f binary/*