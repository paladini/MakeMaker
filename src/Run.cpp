#ifndef RUN_CPP_
#define RUN_CPP_

#include <string>
#include <vector>
#include <iostream>
#include "Command.hpp"
#include "FileManager.hpp"
#include "FileInterpreter.hpp"
#include "CommandInterpreter.hpp"
#include "MakeFile.hpp"
#include "Target.hpp"
#include "Variable.hpp"


int main(int argc, char* argv[]) {
	
	// Creating a makefile
	CommandInterpreter interpreter(argc, argv);
	MakeFile mk = interpreter.parse();

	// std::cout << mk.to_string() << std::endl;
	// std::cout << "variables: " << std::endl;
	// std::cout << mk.list_variables() << std::endl;

	// Creating variables - working!
	// Variable v1("key1", "value1");
	// Variable v2("key2", "value2");
	// Variable v3("key3", "value3");
	// Flag flag1("-output");
	// Flag flag2("-force");
	// File file1("test1.cpp");
	// File file2("test2.cpp");
	
	// Command line1("g++");
	// line1.add_file(file1);
	// line1.add_file(file2);
	// line1.add_flag(flag1);
	// line1.add_flag(flag2);

	// Target t1("myTarget");
	// t1.add_command(line1);
	
	// MakeFile myAwesomeMakefile("makefile");
	// myAwesomeMakefile.add_variable(v1);
	// myAwesomeMakefile.add_variable(v2);
	// myAwesomeMakefile.add_variable(v3);
	// myAwesomeMakefile.add_target(t1);

	// myAwesomeMakefile.save(); 
	
		
};
#endif
