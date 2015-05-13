#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_

#include <string>
// #include <strings.h>
#include <vector>
#include <iostream>
#include "Target.hpp"
#include "FileManager.hpp"
#include "FileInterpreter.hpp"

class MakeFile {

 public:

 	// Antes não chamava esses dois métodos aqui, talvez se faça necessário removê-los.
	MakeFile(std::string path) : _file(path) {
		FileInterpreter fi(_file);
		std::vector<Target> temporary;
		fi.parseFile(&temporary);
		_listTarget = temporary;
	}
	MakeFile(std::string path, bool overwrite) : _file(path) {
		if(!overwrite) {
			FileInterpreter fi(_file);
			std::vector<Target> temporary;
			fi.parseFile(&temporary);
			_listTarget = temporary;
		}

	}

	~MakeFile() {} 

	void save () {
		_file.write(to_string());
	}

	std::string to_string() {
		std::string text = ""; 

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

		return text;
	}

	// TODO: implementar substituição de comandos
	void add_target(Target target) {
		if (check_target_existence(target)) {
			throw -1;
		} else {
			_listTarget.push_back(target);
		}
	}

	void add_target(Target target, bool overwrite) {
		if (check_target_existence(target)) {
			if (overwrite) {
				remove_target(get_target_position(target));
			} else {
				throw -1;
			}
		}
		_listTarget.push_back(target);
	}

	void remove_target() {
		_listTarget.pop_back();
	}

	void remove_target(Target t) {
		int position = get_target_position(t);
		if (position != -1) {
			remove_target(position);
		}
	}

	void remove_target(int pos) {
		_listTarget.erase(_listTarget.begin() + pos);
	}

	// Review it. Before it was marked as "deprecated", but I think it should not be deprecated.
	Target get_or_create_target(char* targetName) {
		Target temp = Target(targetName);
		for(int i = 0; i < _listTarget.size(); i++) {
			if (_listTarget.at(i) == temp) {
				return _listTarget.at(i);
			}
		}

		Target t(targetName);
		return t;
	}
	void add_command_in_target(Target target, Command command) {
		int position = get_target_position(target);
		Target tar = _listTarget.at(position);
		tar.add_command(command);
	}

	std::vector<Target> get_targets() {
		return _listTarget;
	}

	Target* get_target_as_pointer(char* targetName) {
		Target temp = Target(targetName);
		for(int i = 0; i < _listTarget.size(); i++) {
			if (_listTarget.at(i) == temp) {
				return &_listTarget.at(i);
			}
		}
		return NULL;
	}

	Target get_target(int pos) {
		return _listTarget.at(pos);
	}

 private:
 	FileManager _file;
 	std::vector<Target> _listTarget;

 	int get_target_position(Target t) { 
 		for (int i = 0; i < _listTarget.size(); i++) {
 			if (t == _listTarget.at(i)) {
 				return i;
 			}
 		}
 		return -1;
 	}

 	bool check_target_existence(Target t) {
 		return get_target_position(t) != -1;
 	}

};
#endif
