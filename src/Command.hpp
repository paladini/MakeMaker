#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>
#include <list>
#include "Flag.hpp"
#include "Compiler.hpp"
#include "File.hpp"

class Command {
	
 public:
	
	// Constructors
	Command() { }
	~Command() { }
	
	// Methods
	void addFlag(Flag flag) {
		_flags.push_front(flag);
	}
	
	void addFile(File file) {
		_files.push_front(file);
	}
	
	void removeFlag(Flag flagToRemove) {	
		_flags.remove(flagToRemove);
	}
	
	void removeFile(File fileToRemove) {
		_files.remove(fileToRemove);
	}
	
	// Getters & Setters
	std::list<Flag> getFlags() {
		return _flags;
	}	
	
	std::list<File> getFiles() {
		return _files;
	}
	
	void setCompiler(Compiler compiler) {
		_compiler = compiler;
	}
	
	Compiler getCompiler() {
		return _compiler;
	}
	
 private:
	std::list<Flag> _flags;
	std::list<File> _files;
	Compiler _compiler;
}

#endif
