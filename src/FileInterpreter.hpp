#ifndef FILEINTERPRETER_HPP_
#define FILEINTERPRETER_HPP_
#include "Target.hpp"
#include "Command.hpp"
#include "File.hpp"
#include "FileManager.hpp"
#include "Variable.hpp"
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

	void parseFile(std::vector<Target>* targets, std::vector<Variable>* variables) {
		if(_manager.already_exists_a_makefile()){
            std::string content = _manager.read();
            // parseVariables(content, variables);
			foundTargets(content, targets);
		}
	}

 private:

 	FileManager _manager;

    // void parseVariables(std::string content, std::vector<Variable>* variables) {
    //     std::
    // }

	void foundTargets (std::string content, std::vector<Target>* temp) {
    	std::istringstream reader(content);
    	std::string line, newTargetName, variableKey, variableValue;
		int pointsPosition, actual = -1, equalPosition;
        boolean variable = true;
    	while (std::getline(reader, line)) {
            if(line.length() != 0) {
        		pointsPosition = line.find_last_of(":");
                
                // if (variable && pointsPosition == -1) { // 
                    // equalPosition = line.find_last_of("")
                    // variableKey = line.substr(0, )
                // } else {
                    // variable = false;
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
                // }

    		}
    	}
	}

};
#endif