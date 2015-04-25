#ifndef COMPILER_HPP_
#define COMPILER_HPP_

#include <stdio.h>
#include <string>

class Compiler {

 public:
	Compiler(std::string compiler) {
		_compiler = compiler;
	}

	~Compiler() {}

	std::string get_compiler() {
		return _compiler;
	}

	void set_compiler(std::string compiler) {
		_compiler = compiler;
	}

 private:
 	std::string _compiler;
};

#endif
