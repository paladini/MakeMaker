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
		if (check_target_existence(target)) {
			throw -1;
		} else {
			_listTarget.push_back(target);
		}
	}

	void add_target(Target target, int overwrite) {
		if (check_target_existence(target)) {
			if (overwrite) {
				remove_target_at(get_target_position(target));
			} else {
				throw -1;
			}
		}
		_listTarget.push_back(target);
	}

	void remove_target() {
		_listTarget.pop_back();
	}

	void remove_target_at(int pos) {
		_listTarget.erase(_listTarget.begin() + pos);
	}

	// Review it. Before it was marked as "deprecated", but I think it should not be deprecated.
	Target get_or_create_target(char* targetName) {
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

 	int get_target_position(Target target) {
 		for (int i = 0; i < _listTarget.size(); i++) {
 			if (&target == &_listTarget.at(i)) {
 				return i;
 			}
 		}
 	}

 	bool check_target_existence(Target t) {
 		for (int i = 0; i < _listTarget.size(); i++) {
 			if (!strcasecmp(t.get_title(), (_listTarget.at(i)).get_title()) ) {
 				return true;
 			}
 		}
 		return false;
 	}

};
#endif
