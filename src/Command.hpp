#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>
#include <vector>
#include "Flag.hpp"
#include "Compiler.hpp"
#include "File.hpp"

class Command {
	
 public:
	
	// Constructors
	Command(Compiler compiler) : _compiler(compiler) {}
	~Command(){}
	// TODO
	//Command(std::vector<Flag> flags) : _flags(flags) {} 
	//Command(std::vector<File> files) : _files(files) {}
	//Command(std::vector<Flag> flags, std::vector<File> files) : _flags(flags), _files(files) {}
	//Command(Compiler compiler, std::vector<Flag> flags, std::vector<File> files) : _compiler(compiler), _flags(flags), _files(files) {}

	
	// Methods
	void addFlag(Flag flag) {
		_flags.push_back(flag);
	}
	
	void addFile(File file) {
		_files.push_back(file);
	}
	
	// TODO
	std::string toCommand() {
		
		std::string command = _compiler.getCompiler();
		
		// Adding files
		for(int i = 0; i < _files.size(); i++) {
			command += " " + _files.at(i).getPath() ;
		}
		
		// Adding flags
		for(int i = 0; i < _flags.size(); i++) {
			command += " " + _flags.at(i).getFlag();
		}
		
		return command;
	}
	
	// Getters & Setters
	std::vector<Flag> getFlags() {
		return _flags;
	}	
	
	std::vector<File> getFiles() {
		return _files;
	}
	
	void setCompiler(Compiler compiler) {
		_compiler = compiler;
	}
	
	Compiler getCompiler() {
		return _compiler;
	}
	
 private:
	std::vector<Flag> _flags;
	std::vector<File> _files;
	Compiler _compiler;
};

#endif
