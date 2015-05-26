CC=g++
FLAGS=-std=c++11 

# Useless
FLAGS_EXTENDED=-fpermissive -Wformat-security 

all: clean test_compile test

run: run_compile
	cd binary/ &&clear && clear

test:
	cd binary/ && clear && clear && ./Test compiler g++ main.c -o main

test_compile:
	$(CC) src/Test.cpp -o binary/Test $(FLAGS)

run_compile:
	$(CC) src/Run.cpp -o binary/Run.o $(FLAGS)

compile:
	$(CC) src/Command.hpp -o binary/Command.o $(FLAGS)
	$(CC) src/CommandInterpreter.hpp -o binary/CommandInterpreter.o $(FLAGS)
	$(CC) src/Compiler.hpp -o binary/Compiler.o $(FLAGS)
	$(CC) src/File.hpp -o binary/File.o $(FLAGS)
	$(CC) src/FileManager.hpp -o binary/FileManager.o $(FLAGS)
	$(CC) src/FileInterpreter.hpp -o binary/FileInterpreter.o $(FLAGS)
	$(CC) src/Flag.hpp -o binary/Flag.o $(FLAGS)
	$(CC) src/MakeFile.hpp -o binary/MakeFile.o $(FLAGS)
	$(CC) src/Target.hpp -o binary/Target.o $(FLAGS)
	$(CC) src/Test.cpp -o binary/Test.o $(FLAGS)
	$(CC) src/Run.cpp -o binary/Run.o $(FLAGS)

debug: clean
	$(CC) src/Test.cpp -o binary/Test $(FLAGS) -g

clean:
	rm -f binary/*