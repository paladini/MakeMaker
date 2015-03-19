/*
	This class parse a command that was given from the command line.
	You can use `makemaker` to run all these commands or just `mm` (an alias).

	Specification TODO:
		- Think about <command> abstraction. What if user wants to compiler
		  a lot of files in a single command? ("g++ rola.cpp hard.cpp shora.c -o main")

	Current specification:
		
		# Creating/Editing Target:
			This command will create a target if it doesn't exist, 
			and edit it, otherwise.

			mm <target>
		
		# Adding command to target
			mm <target> <command>
			mm <target> "<literal_command>"

			Where <command> is just:
				<compiler> <all|*.extension|filename.*|filename.extension> <flags>

			Where "<literal_command>" can be any command you like:
				grep -js | "pasdpokasd"
		
		# Replacing command:
			mm <target>:<number_line> <command>
			mm <target>:<number_line> "<literal_command>"

			Where <command> is just:
				<compiler> <all|*.extension|filename.*|filename.extension> <flags>

		# Deleting target
			mm ! <target>

		# Deleting full command
			mm ! <target>:<number_line>
	
		# Deleting compiler
			mm ! <target>:<number_line> -c

		# Deleting filename
			mm ! <target>:<number_line> -f <all|*.extension|filename.*|filename.extension>

		# Deleting flag 
			mm ! <target>:<number_line> -F <flags>
  
*/

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <stdio.h>
#include <iostream>

using namespace std;

class Interpreter {

 public:
 	Interpreter(int argc, char** argv) : _argc(argc), _argv(argv) {}

 	void parse() { }

 	// Remove later.
 	void print_params() {
 		cout << "Argc = " << _argc << endl;
 		cout << "Argv: " << endl;
 		for(int i = 0; i < _argc; i++) {
 			cout << _argv[i] << endl;
 		}
 	}

 private:
 	int _argc;
 	char** _argv;
};
#endif