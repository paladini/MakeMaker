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
	FileInterpreter (FileManager manager) {
		_manager = manager;
	}

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
		int pointsPosition, actual = 0;

    	while (std::getline(reader, line)) {
    		pointsPosition = line.find_last_of(":");
    		if(line.length() != 0) {
    			if((line.at(0) != '\t') && (pointsPosition != -1)) {
    				newTargetName = line.substr(0, pointsPosition);
    				char* name = (char*) malloc (newTargetName.size() + 1);
    				memcpy(name, newTargetName.c_str(), newTargetName.size() + 1);
    				Target t = Target(name);
					temp->push_back(t);
    			} else {
					temp->at(actual).add_command(readCommand(line));
					actual++;
    			}
    		}
    	}
	}

	Command readCommand(std::string line) {
		std::string temp, next;
		std::vector<File> files;
		std::vector<Flag> flags;

		std::istringstream iss(line);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		Command command(tokens.at(0));
		for (int i = 1; i < tokens.size(); i++) {
			temp = tokens.at(i);

			if(temp.at(0) != '-') {
				files.push_back(temp);
			} else { // flag

				// Remember, we can have a flag like that: "-o MyOutputName teste -c -d"
				// We need to check the next string until the first character of the next
				// strng is a "-".
				for (int j = i+1; j < tokens.size(); j++) {
					next = tokens.at(j);
					if(next.at(0) != '-') {
						temp += " " + next;
						i++;
					}
				}
				flags.push_back(temp);
			}
		}

		command.add_files(files);
		command.add_flags(flags);
		return command;
	}
};
#endif