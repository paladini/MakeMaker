#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_

#include <string>
#include <strings.h>
#include <vector>
#include <iostream>
#include "Target.hpp"
#include "FileManager.hpp"
#include "FileInterpreter.hpp"

class MakeFile {

 public:
	MakeFile(std::string path) : _file(path) {	}
	MakeFile(std::string path, bool overwrite) : _file(path) {
		if(!overwrite) {
			FileInterpreter fi(path);
			_listTarget = fi.parseFile();
		}
	}

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
		if (check_target_existence(target)) {
			throw -1;
		} else {
			_listTarget.push_back(target);
		}
	}

	void remove_target() {
		_listTarget.pop_back();
	}

	// Deprecated. To be removed.
	Target get_or_create_target(std::string targetNameString) {
		char* targetName = &targetNameString[0];

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

	std::vector<Target> get_targets() {
		return _listTarget;
	}

	Target get_target(int pos) {
		return _listTarget.at(pos);
	}

 private:
 	FileManager _file;
 	std::vector<Target> _listTarget;

 	bool check_target_existence(Target t) {
 		for (int i = 0; i < _listTarget.size(); i++) {
 			//std::cout << "t(title): " << std::string(t.get_title()) << std::endl;
 			//std::cout << "_listTarget(i)(title): " << std::string(_listTarget.at(i).get_title()) << std::endl;
 			if ( strcasecmp(t.get_title(), _listTarget.at(i).get_title()) ) {
 				return true;
 			}
 		}
 		return false;
 	}

};
#endif
