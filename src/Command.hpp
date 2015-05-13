#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>
#include <string.h>
#include <vector>
#include "Flag.hpp"
#include "Compiler.hpp"
#include "File.hpp"

class Command {
	
 public:
	
	// Constructors
	Command() : _compiler("gg") {}
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
	
 private:
	std::vector<Flag> _flags;
	std::vector<File> _files;
	Compiler _compiler;
};

#endif
