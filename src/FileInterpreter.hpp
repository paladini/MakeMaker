#ifndef FILEINTERPRETER_HPP_
#define FILEINTERPRETER_HPP_
#include "Target.hpp"
#include "Command.hpp"
#include "File.hpp"
#include "FileManager.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

class FileInterpreter {
 public:
	FileInterpreter (FileManager* manager) {
		_manager = *manager;
	}
    ~FileInterpreter() {}

	void parseFile(std::vector<Target>* temp) {
		if(_manager.already_exists_a_makefile()){
			foundTargets(_manager.read(), temp);
		}
	}

 private:

 	FileManager _manager;

	void foundTargets (std::string content, std::vector<Target>* temp) {
    	std::istringstream reader(content);
    	std::string line, newTargetName;
		int pointsPosition, actual = -1;
    	while (std::getline(reader, line)) {
    		pointsPosition = line.find_last_of(":");
    		
    		if(line.length() != 0) {
    			if((line.at(0) != '\t') && (pointsPosition != -1)) {
    				newTargetName = line.substr(0, pointsPosition);
    				char* name = (char*) malloc (newTargetName.size() + 1);
    				memcpy(name, newTargetName.c_str(), newTargetName.size() + 1);
    				Target t = Target(name);
					temp->push_back(t);
					actual++;
    			} else {
    				Command c;
    				c.parse(line);
					temp->at(actual).add_command(c);
    			}
    		}
    	}
	}

};
#endif