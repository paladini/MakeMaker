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
            foundTargets(content, targets, variables);
        }
    }

 private:

 	FileManager _manager;

	void foundTargets (std::string content, std::vector<Target>* temp, std::vector<Variable>* variables) {
    	std::istringstream reader(content);
    	std::string line, newTargetName, key, value;
		int pointsPosition, actual = -1, variableSeparator;
        bool variable = true;
    	while (std::getline(reader, line)) {
            if(line.length() != 0) {
        		pointsPosition = line.find_last_of(":");
                if (variable) {
                    variableSeparator = line.find_last_of("=");
                }

                if (variableSeparator != -1 && pointsPosition == -1) { 
                    key = line.substr(0, variableSeparator);
                    value = line.substr(variableSeparator+1);

                    char* tempKey = (char*) malloc (key.size()+1);
                    char* tempValue = (char*) malloc (value.size()+1);
                    memcpy(tempKey, key.c_str(), key.size()+1);
                    memcpy(tempValue, value.c_str(), value.size()+1);
                    
                    Variable v(tempKey, tempValue);
                    variables->push_back(v);
                    
                } else if((line.at(0) != '\t') && (pointsPosition != -1)) {
                    variable = false;
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