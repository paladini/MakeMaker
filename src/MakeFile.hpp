#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_

#include <string>
#include <list>
#include "Target.hpp"

class MakeFile {

 public:
	MakeFile(std::string path) { 
		_file(path);
	}

 private:
 	FileManager _file;
 	std::list<Target> listTarget;

};
#endif