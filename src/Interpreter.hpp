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
#include <string>
#include <string.h>
#include <vector>
#include "MakeFile.hpp"
#include "Target.hpp"
// #include <cstring>

using namespace std;

class Interpreter {

 public:
 	Interpreter (int argc, char** argv, MakeFile mk) : _argc(argc), _argv(argv), _mk(mk) { }

 	// TODO: enable that.
 	// Interpreter (string content, MakeFile mk) {
 	// 	_mk = mk;

		// // Converting string (aka "My string with spaces" -> ['my', 'string', 'with', 'spaces']) into vector of chars.
		// vector<char> v(content.begin(), content.end());

		// // Get argc
		// _argc = v.size();

		// // Convert vector<char> to char* [].
		// std::copy(v.begin(), v.end(), _argv);
 	// }

 	void parse() {

 		// Checks if no argument was given to program.
 		if(_argc == 1) {
 			print_usage();
 			return;
 		}

 		// Check if the action as an delete action.
 		if(_argv[1] == "!") {
 			parse_delete();
 		} else {
 			parse_add();
 		} 

 	}


 private:

 	// TODO: implement that.
 	void parse_add() { 

 		// Get the target
		Target target = mk.get_or_add_target(_argv[1]);
 		// std::string target = _argv[1];

 		// TODO
 		if (_argv > 1) {

 		}

 	}

 	void parse_delete() {

 		// If only target was given, delete target.
 		if(_argc == 3) {
 			// TODO Delete the given target.
 			return;
 		}

 		// Cause there's 4 arguments, must determine what's the used flag (-c, -f, -F)
 		// Fazer de uma forma melhor.
 		if(_argv[4] == "-c"){
 			return;
 		} else if(_argv[4] == "-f") {
 			return;
 		} else if(_argv[4] == "-F") {
 			return;
 		} else {
 			cout << "Problem!" << endl;
 		}

 	}

 	void print_usage() {
 		printf(usage.c_str());
 	}

 	// Remove later.
 	void print_params() {
 		char *args = _argv[1];
 		cout << "Argc = " << _argc << endl;
 		for(int i = 2; i < _argc; i++) {
 			strcat(args, " ");
 			strcat(args, _argv[i]);
 		}
 		//cout << args << endl;
 		FileManager create("archive");
 		create.write(args);
 		cout << "Criado!" << endl;
 	}

 	/* void print_noArguments() {
 		printf(noArguments.c_str());
 		int option = -1;
 		printf("\nDo you like to see instructions about how to use this software? (1/0)");
 		while(option != 0 && option != 1) {
 			cin >> option;
 		}
 		
 		if(option == 1) {
			printf(usage.c_str()); 			
 		} 
 	} */

 	// Variables
 	int _argc;
 	char** _argv;
 	MakeFile _mk;

 	// Messages (constants)
 	const std::string 
 		noArguments = "No arguments is given, try again using the correct parameters.\n",
 		usage = "======================================================================\n" \
 				"    MakeMaker is an easy-to-use tool that generate makefiles.\n" \
 				"\n    Currently there's no GUI interface for this tool, so you must" \
 				"\n    create your makefiles by command line. Following you can check" \
 				"\n    the usage of this tool. Hope it helps you.\n" 
 				"\n    This software's distribued under the MIT license.\n" \
 				"======================================================================\n" \
 				"\n    Usage:\n" \
 				"\n\t# Create / Edit a Target:" \
 				"\n\tmm <target>\n" \
 				"\n\t# Adding command to Target:" \
 				"\n\tmm <target> <command>\n";
};
#endif