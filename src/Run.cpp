#include "Command.hpp"
#include "FileManager.hpp"
#include "Interpreter.hpp"
#include "MakeFile.hpp"

int main(int argc, char* argv[]) {
	
	// Creating a makefile
	//MakeFile mk("makefile");

	Interpreter interpreter(argc, argv);
	MakeFile* mk = interpreter.parse();

	mk->save();

	/* Usage example:
	Flag flag1("-output");
	Flag flag2("-force");
	
	Compiler gpp("g++");
	
	File file1("test1.cpp");
	File file2("test2.cpp");
	
	Command line1(gpp);
	line1.addFile(file1);
	line1.addFile(file2);
	line1.addFlag(flag1);
	line1.addFlag(flag2);
	
	FileManager myAwesomeMakefile("makefile");
	myAwesomeMakefile.write(line1.toCommand()); */
	
		
}
