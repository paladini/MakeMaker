#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <stdio.h>
#include <string>

class Compiler {

 public:
	Compiler(std::string compiler) {
		_compiler = compiler;
	}

	std::string getCompiler() {
		return _compiler;
	}

	void setCompiler(std::string compiler) {
		_compiler = compiler;
	}

 private:
 	std::string _compiler;
};

#endif
