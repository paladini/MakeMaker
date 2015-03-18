#ifndef COMPILER_HPP_
#define COMPILER_HPP_
#include <stdio.h>
class Compiler {

 public:
	Compiler(string compiler) {
		_compiler = compiler;
	}

	string getCompiler() {
		return _compiler;
	}

	void setCompiler(string compiler) {
		_compiler = compiler;
	}

 private:
 	string _compiler;
}