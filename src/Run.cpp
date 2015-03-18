#include "Command.hpp"

int main(int argc, char* argv[]) {
	
	// Flags
	Flag flag1("-output");
	Flag flag2("-force");
	
	// Compiler
	Compiler gpp("g++");
	
	// Files	
	File file1("test1.cpp");
	File file2("test2.cpp");
	
	// Criando o comando e associando com files, compiler e flags
	Command line1(gpp);
	line1.addFile(file1);
	line1.addFile(file2);
	line1.addFlag(flag1);
	line1.addFlag(flag2);
	
	// Criando um arquivo
	FileManager myAwesomeMakefile("makefile");
	
		
}
