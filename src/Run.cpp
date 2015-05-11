#ifndef RUN_CPP_
#define RUN_CPP_

#include <string>
// #include <strings.h>
#include <vector>
#include <iostream>
#include "Command.hpp"
#include "FileManager.hpp"
#include "FileInterpreter.hpp"
#include "CommandInterpreter.hpp"
#include "MakeFile.hpp"
#include "Target.hpp"


int main(int argc, char* argv[]) {
	
	// Creating a makefile
	//MakeFile mk("makefile");
	// CommandInterpreter interpreter(argc, argv);
	// MakeFile mk = interpreter.parse();

	// Test for the makefile parsing.
	MakeFile _mk("makefile", false);
	std::cout << "Nome do target no Run.cpp: " << std::string(_mk.get_target(0).get_title()) << std::endl;

	// <!-- EXEMPLO DO PROBLEMA ESTÁ AQUI, DENTRO DO MAKEFILE ELE IMPRIME O GET_TITLE CERTO
	// MAS DEPOIS QUE ELE SAIU DO CONSTRUTOR COMEÇA A IMPRIMIR O GET_TITLE ERRADO. -->
	std::cout << "\n=========================\nImprimindo todo o Makefile interpretado: \n" << std::endl;
	std::cout << _mk.to_string() << std::endl;

	/* Usage example:
	Flag flag1("-output");
	Flag flag2("-force");
	
	Compiler gpp("g++");
	
	File file1("test1.cpp");
	File file2("test2.cpp");
	
	Command line1(gpp);
	line1.add_file(file1);
	line1.add_file(file2);
	line1.add_flag(flag1);
	line1.add_flag(flag2);
	
	FileManager myAwesomeMakefile("makefile");
	myAwesomeMakefile.write(line1.to_command()); */
	
		
};
#endif
