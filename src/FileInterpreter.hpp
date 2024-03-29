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
	FileInterpreter () {}

    ~FileInterpreter() {}

    void parseFile(std::vector<Target>* targets, std::vector<Variable>* variables) {
        FileManager* _manager = FileManager::get_singleton();
        if(_manager->already_exists_a_makefile()){
            std::string content = _manager->read();
            foundTargets(content, targets, variables);
        }
    }

 private:

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
                    Variable v(line);
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