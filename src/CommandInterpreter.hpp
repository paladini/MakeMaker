/*
	This class parse a command that was given from the command line.
	You can use `mm` to run all these commands.

	Current specification:

		# Creating/Editing Target
			This command will create a target if it doesn't exist.

			mm add <target>
		
		# Adding command to target
			mm add <target> <command>

			Where <command> is
				<compiler> <filename.ext, filename2.ext, ...> <flags>
		
		# Target rename
			mm edit <oldTargetName> <newTargetName>

		# Replacing command
			mm edit <target>:<number_line> <command>

			Where <command> is just
				<compiler> <filename.ext, filename2.ext, ...> <flags>

		# Deleting target
			mm remove <target>

		# Deleting full command
			mm remove <target>:<number_line>
	
*/

#ifndef COMMAND_INTERPRETER_HPP_
#define COMMAND_INTERPRETER_HPP_

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <exception>			
#include "MakeFile.hpp"
#include "Target.hpp"
#include "Command.hpp"
#include "exceptions/InsufficientArguments.hpp"
#include "exceptions/SomethingWrongException.hpp"

class CommandInterpreter {

 public:
 	CommandInterpreter (int argc, char** argv) : _argc(argc), _argv(argv), _mk("makefile", false)  {} 
 	~CommandInterpreter() {}

 	MakeFile parse() {
 		if (_argc < 2) {
 			print_usage();
 		} else if (!strcasecmp(_argv[1], "list")){
	 		parse_list();
	 	} else {
 			if(_argc == 2) {
	 			print_usage();
	 		} else if(!strcasecmp(_argv[1], "add")) {
	 			parse_add();
	 		} else if(!strcasecmp(_argv[1], "remove")) {
	 			parse_delete();
	 		} else if(!strcasecmp(_argv[1], "edit")) {
	 			parse_edit();
	 		} else {
	 			throw SomethingWrongException();
	 		}
	 		_mk.save();
 		}
		return _mk;
 	}


 private:

 	void parse_add() {

		Target target(_argv[2]);
 		std::string targetName = std::string(target.get_title());

		char* name = get_target_name(targetName);
		target = _mk.get_or_create_target(name);

		Command command;
 		if (_argc > 3) {
 			std::string myAwesomeCommand = std::string(_argv[3]) + " ";
			for(int i = 4; i<_argc; i++) {
				myAwesomeCommand += std::string(_argv[i]) + " ";
			}
			command.parse(myAwesomeCommand);
			target.add_command(command);
		}

 		// TODO:
		//	Differences between "mm <target> <command>" and "mm <target>:<lineOfCommand> <command>", where:
		//      - In the first case, add a new target.
		//      - In the second case, overwrites a command (given by the "lineOfCommand"). 

 		// 	Compiler compiler(_argv[3]);
 		// 	command.set_compiler(compiler);

 		// 	std::vector<File> files = parse_files();
 		// 	command.add_files(files);

 		// 	int startsAt = 4 + files.size();
 		// 	std::vector<Flag> flags = parse_flags(startsAt);
 		// 	command.add_flags(flags);
 		
 		_mk.add_target(target, true);

 	}

 	void parse_delete() {
 		if(_argc == 3) {
 			char* targetName = get_target_name(std::string(_argv[2]));
 			Target t(targetName);

 			int line_number = get_line_number(std::string(_argv[2]));
 			if (line_number != -1) {
 				_mk.remove_command_from_target(t, line_number);
 			} else {
	 			_mk.remove_target(t);
 			}
 		}
 	}

 	void parse_edit() {
 		int lineNumber = -1;
		Target* target = new Target(_argv[2]);
 		std::string targetName = std::string(target->get_title());

		lineNumber = get_line_number(targetName);
		char* name = get_target_name(targetName);
		target = _mk.get_target_as_pointer(name);
		
		Command command;

 		if(lineNumber == -1 && target != NULL && _argc == 4) {
 			name = _argv[3];
 			target->set_title(name);
 		} else if(lineNumber != -1) {
 			Target old = *target;
 			Compiler compiler(_argv[3]);
 			command.set_compiler(compiler);
 			std::vector<File> files = parse_files();
 			command.add_files(files);
 			int startsAt = 4 + files.size();
 			std::vector<Flag> flags = parse_flags(startsAt);
 			command.add_flags(flags);
 			old.add_command(command, lineNumber);
 			_mk.add_target(old, true);
 		} else if (target == NULL) {
 			throw -3;
 		} else {
 			throw -4;
 		}
 	}

 	void parse_list() {
 		if (_argc == 2) {
	 		std::cout << _mk.list_targets() << std::endl;
 			return;
 		} else if (_argc == 3) {
 			if (!strcasecmp(_argv[2], "-A")) {
 				std::cout << _mk.to_string() << std::endl;
 			} else {
	 			std::cout << _mk.list_target(_argv[2]) << std::endl;
 			}
 		} else {
 			throw SomethingWrongException();
 		}
 	}

 	std::vector<Flag> parse_flags(const int startsAt) {
 		int i = startsAt;
 		std::vector<Flag> flags;

 		while (i < _argc) {
 			std::string flg = _argv[i];
 			Flag flag(flg);
 			flags.push_back(flag);
 			i++;
 		}

 		return flags;
 	}

 	std::vector<File> parse_files() {
 		int i = 4;
 		std::vector<File> files;
 		std::string input = _argv[4];

 		while (input[0] != '-') {
 			File file(input);
 			files.push_back(file);
 			i++;
	 		input = _argv[i];
 		}

 		return files;
 	}

 	int get_line_number(std::string targetName) {
 		int temp = targetName.find_last_of(":");
 		if (temp != -1) {
 			temp = std::stoi(targetName.substr(temp + 1, targetName.length()));
 		}
 		return temp;
 	}

 	char* get_target_name(std::string targetName) {
 		int temp = targetName.find_last_of(":");
 		if (temp != -1) {
	 		std::string newTargetName = targetName.substr(0, temp);
	 		char* name = (char*) malloc (newTargetName.size() + 1);
    		memcpy(name, newTargetName.c_str(), newTargetName.size() + 1);
	 		return name;
	 	} 
	 	char* name = (char*) malloc (targetName.size() + 1);
    	memcpy(name, targetName.c_str(), targetName.size() + 1);
    	return name;
 	}	

 	void print_usage() {
 		std::cout << usage << std::endl;
 	}

 	int _argc;
 	char** _argv;
 	MakeFile _mk;

 	const std::string usage = "======================================================================\n" \
 				"    MakeMaker is an easy-to-use tool that generate makefiles.\n" \
 				"\n    Currently there's no GUI interface for this tool, so you must" \
 				"\n    create your makefiles by command line. Following you can check" \
 				"\n    the usage of this tool. Hope it helps you.\n" 
 				"\n    This software's distributed under the MIT license.\n" \
 				"======================================================================\n" \
 				"\n    Usage:" \
 				"\n\n\t# Create target" \
				"\n\tmm add <target>" \
				"\n\n\t# Add command to target" \
				"\n\tmm add <target> <command>" \
				"\n\n\t    Where <command> is:" \
				"\n\t    <compiler> <filename.ext, filename2.ext, ...> <flags>"  \
				"\n\n\t# Rename target" \
				"\n\tmm edit <oldTargetName> <newTargetName>" \
				"\n\n\t# Replace command" \
				"\n\tmm edit <target>:<number_line> <command>" \
				"\n\n\t    Where <command> is:" \
				"\n\t    <compiler> <filename.ext, filename2.ext, ...> <flags>"  \
				"\n\n\t# Delete target" \
				"\n\tmm remove <target>" \
				"\n\n\t# Delete command from target" \
				"\n\tmm remove <target>:<number_line>\n";
};
#endif
