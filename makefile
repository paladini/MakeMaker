CC=g++

all: test_compile test_run

test_compile:
	$(CC) src/Run.cpp -o binary/Run

test_run:
	cd binary/ && ls && ./Run testando

compile:
	$(CC) src/Flag.hpp -o binary/Flag.o
	$(CC) src/Compiler.hpp -o binary/Compiler.o
	$(CC) src/File.hpp -o binary/File.o
	$(CC) src/Command.hpp -o binary/Command.o