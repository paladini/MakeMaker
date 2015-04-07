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
#include "Command.hpp"
// #include <cstring>

using namespace std;

class Interpreter {

 public:
 	Interpreter (int argc, char** argv) : _argc(argc), _argv(argv) { }

 	// TODO: enable that.
 	// Interpreter (string content, MakeFile mk) {
 	// 	_mk = mk;

	    // Converting string (aka "My string with spaces" -> ['my', 'string', 'with', 'spaces']) into vector of chars.
		// vector<char> v(content.begin(), content.end());

		// // Get argc
		// _argc = v.size();

		// // Convert vector<char> to char* [].
		// std::copy(v.begin(), v.end(), _argv);
 	// }

 	MakeFile* parse() {

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

 		return _mk;
 	}


 private:

 	// TODO: implement that.
 	void parse_add() { 

 		// mm <target>  <command>
 		// TODO: I guess it's something wrong here.
 		// Get the target

		// Target* target = _mk->get_or_add_target(_argv[1]);
 		Target target(_argv[1]);

		// Generating new command
		Command* command = new Command();

 		// TODO:
		//	Differences between "mm <target> <command>" and "mm <target>:<lineOfCommand> <command>", where:
		//      - In the first case, add a new target.
		//      - In the second case, overwrites a command (given by the "lineOfCommand"). 
 		if (_argc > 1) {

 			// Get compiler
 			Compiler* compiler = new Compiler(_argv[2]);
 			command->setCompiler(compiler);

 			//printf("Compilador: %s", compiler->getCompiler());
 			std::cout << "Compilador: " << compiler->getCompiler() << endl;

 			// Get files
 			std::vector<File> files = parse_files();
 			command->addFiles(files);

 			for(int i = 0; i < files.size(); i++){
	 			std::cout << "File[" << i << "]: " << files.at(i).getPath() << endl;
 			}

 			// Get flags
 			int startsAt = 2 + files.size();
 			std::vector<Flag> flags = parse_flags(startsAt);
 			command->addFlags(flags);

 			for(int i = 0; i < flags.size(); i++){
	 			std::cout << "Flags[" << i << "]: " << flags.at(i).getFlag() << endl;
 			}

 			// Adding command to target
 			target.addCommand(command);

 		}

 		_mk->add_target(target);

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

 	std::vector<Flag> parse_flags(const int startsAt) {
 		int i = startsAt;
 		std::vector<Flag> flags;

 		while(i < _argc) {
 			std::string flg = _argv[i];
 			Flag flag(flg);
 			flags.push_back(flag);
 			i++;
 		}

 		return flags;
 	}

 	std::vector<File> parse_files() {
 		int i = 3;
 		std::vector<File> files;
 		std::string input = _argv[3];

 		while(input.at(0) != '-') {
	 		input = _argv[i];
 			File file(input);
 			files.push_back(file);
 			i++;
 		}

 		return files;
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
 	MakeFile* _mk = new MakeFile("makefile");

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