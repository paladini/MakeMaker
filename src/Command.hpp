#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>
#include <string.h>
#include <vector>
#include "Flag.hpp"
#include "Compiler.hpp"
#include "File.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>


class Command {
	
 public:
	
	// Constructors
	Command() : _compiler("gg") {}
	// Command(std::string commandLine) { parse(commandLine); }
	Command(std::string compiler) : _compiler(compiler) {}
	~Command(){}
	// TODO
	//Command(std::vector<Flag> flags) : _flags(flags) {} 
	//Command(std::vector<File> files) : _files(files) {}
	//Command(std::vector<Flag> flags, std::vector<File> files) : _flags(flags), _files(files) {}
	//Command(Compiler compiler, std::vector<Flag> flags, std::vector<File> files) : _compiler(compiler), _flags(flags), _files(files) {}

	
	// Methods
	void set_files(std::vector<File> files) {
		_files = files;
	}

	void set_flags(std::vector<Flag> flags) {
		_flags = flags;
	}

	/* void add_files(std::vector<File> files) {
		bool fileExists = 0;
		for (int i = 0; i < files.size(); i++) {
			for (int j = 0; j < _files.size(); j++) {
				if ( strcasecmp(files.at(i).get_path(), _files.at(j).getFile()) ) {
					fileExists = 1;
					break;
				}
			}

			if(fileExists == 0) {
				_files.push_back(files.at(i));
			}
			fileExists = 0;
		}
	} */

	void add_flag(Flag flag) {
		_flags.push_back(flag);
	}

	void add_flags(std::vector<Flag> flags) {
		for (int i = 0; i < flags.size(); i++) {
			_flags.push_back(flags.at(i));
		}
	}

	void add_file(File file) {
		_files.push_back(file);
	}

	void add_files(std::vector<File> files) {
		for (int i = 0; i < files.size(); i++) {
			_files.push_back(files.at(i));
		}
	}
	
	// TODO
	std::string to_command() {
		
		std::string command = "\t" + _compiler.get_compiler();
		
		// Adding files
		for(int i = 0; i < _files.size(); i++) {
			command += " " + _files.at(i).get_path() ;
		}
		
		// Adding flags
		for(int i = 0; i < _flags.size(); i++) {
			command += " " + _flags.at(i).get_flag();
		}
		
		return command;
	}
	
	// Getters & Setters
	std::vector<Flag> get_flags() {
		return _flags;
	}	
	
	std::vector<File> get_files() {
		return _files;
	}
	
	void set_compiler(Compiler compiler) {
		_compiler = compiler;
	}
	
	Compiler get_compiler() {
		return _compiler;
	}

	void parse(std::string line) {
		std::string temp, next;

		std::istringstream iss(line);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		set_compiler(tokens.at(0));
		for (int i = 1; i < tokens.size(); i++) {
			temp = tokens.at(i);

			if(temp.at(0) != '-') {
				add_file(temp);
			} else { // flag

				// Remember, we can have a flag like that: "-o MyOutputName -c -d"
				// "-o MyOutputName" must be a single flag (a flag that have one argument). We must parse it, the code below care that.
				if ((i+1) < tokens.size()) {
					next = tokens.at(i+1);
					if(next.at(0) != '-') {
						temp += " " + next;
						i++;
					}	
				}
				add_flag(temp);

			}
		}
	}
	
 private:
	std::vector<Flag> _flags;
	std::vector<File> _files;
	Compiler _compiler;
};

#endif
