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

 	void parse_add() { 

 		int lineNumber = -1;
 		std::string targetName = string(_argv[1]);
		Target target(targetName.c_str());
		
		// Converting myTarget:myLine into myTarget, if ":" exists.
		int pointsPosition = targetName.find_last_of(":");
		if(pointsPosition != -1) {
			std::string newTargetName = targetName.substr(0, pointsPosition);
			lineNumber = std::stoi(targetName.substr(pointsPosition + 1, targetName.length()));
			
			target = _mk->get_or_create_target(newTargetName.c_str());
		} 
		
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

 			// Get files
 			std::vector<File> files = parse_files();
 			command->addFiles(files);

 			// Get flags
 			int startsAt = 3 + files.size();
 			std::vector<Flag> flags = parse_flags(startsAt);
 			command->addFlags(flags);

 			// Adding command to target
 			if (lineNumber != -1) {
				target.addCommand(command, lineNumber);
			} else {
				target.addCommand(command);
			} 
			
			// Print debug
			// print_debug();
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

 		while(input[0] != '-') {
 			File file(input);
 			files.push_back(file);
 			i++;
	 		input = _argv[i];
 		}

 		return files;
 	}
 	
 	// TODO (not working).
 	void print_debug() {
		
		Command command = _mk->getTarget(0).getCommands().at(0);
		
		std::cout << "Compilador: " << command.getCompiler() << endl;
		
		for(int i = 0; i < command.getFiles().size(); i++){
	 		std::cout << "File[" << i << "]: " << command.getFiles().at(i).getPath() << endl;
 		} 
		
		for(int i = 0; i < command.getFlags().size(); i++){
	 		std::cout << "Flags[" << i << "]: " << command.getFlags().at(i).getFlag() << endl;
 		}
	}

 	void print_usage() {
 		printf(usage.c_str());
 	}

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
