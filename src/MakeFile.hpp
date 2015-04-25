#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_

#include <string>
#include <strings.h>
#include <vector>
#include <iostream>
#include "Target.hpp"
#include "FileManager.hpp"

class MakeFile {

 public:
	MakeFile(std::string path) : _file(path) {}
	~MakeFile() {} 

	void save () {
		std::string text; 

		// Load all targets and put everything inside a string.
		for(int i = 0; i < _listTarget.size(); i++) {
			Target that = _listTarget.at(i);

			std::string temp = std::string(that.get_title()) + ":";
			std::vector<Command> listCommands = that.get_commands();
			for(int j = 0; j < listCommands.size(); j++) {
				temp += "\n" + listCommands.at(j).to_command();
			}

			text += temp + "\n";
			if (i + 1 < _listTarget.size()) {
				text += "\n";
			}
		}

		// Saving to the file
		_file.write(text);
	}

	// TODO: implementar substituição de comandos
	void add_target(Target target) {
		_listTarget.push_back(target);
	}
	
	Target get_target(int pos) {
		return _listTarget.at(pos);
	}

	// Deprecated. To be removed.
	Target get_or_create_target(char* targetName) {
		
		// Check if already exists
		for(int i = 0; i < _listTarget.size(); i++) {
			if ( strcasecmp((_listTarget.at(i)).get_title(), targetName) ) {
				return _listTarget.at(i);
			}
		}

		// If not, add.
		Target t(targetName);
		return t;
	}

 private:
 	FileManager _file;
 	std::vector<Target> _listTarget;

};
#endif
