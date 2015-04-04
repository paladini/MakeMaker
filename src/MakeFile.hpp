#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_

#include <string>
#include <strings.h>
#include <vector>
#include "Target.hpp"

class MakeFile {

 public:
	MakeFile(std::string path) { 
		_file = new FileManager(path);
	}

	void save() {
		std::string text; 

		// Load all targets and put everything inside a string.
		for(int i = 0; i < _listTarget.size(); i++) {

			Target that = _listTarget.at(i);
			std::string temp = strcat(that.getTitle(), ":");
			std::vector<Command> listCommands = that.getCommands();
			for(int j = 0; j < listCommands.size(); j++) {
				temp += "\n" + listCommands.at(j).toCommand();
			}

			text += temp + "\n";
		}

		// Saving to the file
		_file->write(text);
	}

	Target get_or_add_target(char* targetName) {
		
		// Check if already exists
		for(int i = 0; i < _listTarget.size(); i++) {
			if ( strcasecmp((_listTarget.at(i)).getTitle(), targetName) ) {
				return _listTarget.at(i);
			}
		}

		// If not, add.
		Target t(targetName);
		_listTarget.push_back(t);
		return t;
	}

 private:
 	FileManager * _file;
 	std::vector<Target> _listTarget;

};
#endif