#ifndef MAKEFILE_HPP_
#define MAKEFILE_HPP_
#include <string>
#include <vector>
#include <iostream>
#include "Target.hpp"
#include "FileManager.hpp"
#include "FileInterpreter.hpp"
#include "Variable.hpp"

class MakeFile {

 public:

	MakeFile(std::string path) : _file(path) {
		FileInterpreter fi(&_file);
		std::vector<Target> temporary;
		std::vector<Variable> tempVariables;
		fi.parseFile(&temporary, &tempVariables);
		_listTarget = temporary;
		_listVariable = tempVariables;
	}
	MakeFile(std::string path, bool overwrite) : _file(path) {
		if (!overwrite) {
			FileInterpreter fi(&_file);
			std::vector<Target> temporary;
			std::vector<Variable> tempVariables;
			fi.parseFile(&temporary, &tempVariables);
			_listTarget = temporary;
			_listVariable = tempVariables;
		}
	}

	~MakeFile() {} 

	void save () {
		_file.write(to_string());
	}

	std::string to_string() {
		std::string text = ""; 

		// Load all variables
		for (int i = 0; i < _listVariable.size(); i++) {
			text += std::string(_listVariable.at(i).get_key()) + "=" \
					+ std::string(_listVariable.at(i).get_value()) + "\n";
			if (i + 1 == _listVariable.size()) {
				text += "\n";
			}
		}

		// Load all targets and put everything inside a string.
		for (int i = 0; i < _listTarget.size(); i++) {
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

	void add_variable(Variable var) {
		if (check_variable_existence(var)) {
			remove_variable(var);
		}
		_listVariable.push_back(var);
	}

	void remove_variable() {
		_listVariable.pop_back();
	}

	void remove_variable(char* variableChar) {
		std::string v = std::string(variableChar);
		int position = v.find_last_of("=");
		v = v.substr(0, position);
		Variable* myVariable = get_variable(v);
		if (myVariable != NULL) {
			remove_variable(*myVariable);
		}
	}

	void remove_variable(Variable v) {
		int position = get_variable_position(v);
		if (position != -1) {
			remove_variable(position);
		}
	}

	void remove_variable(int pos) {
		_listVariable.erase(_listVariable.begin() + pos);
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


	void add_command_in_target(Target t, Command command) {
		int position = get_target_position(t);
		Target tar = _listTarget.at(position);
		tar.add_command(command);
	}

	void remove_command_from_target(Target t, int line) {
		// int position = get_target_position(t);
		// Target tar = _listTarget.at(position);
		Target* tar = get_target_as_pointer(t.get_title());
		tar->remove_command(line);

		if (tar->get_commands().size() == 0) {
			remove_target(*tar);
		}
	}

	std::string list_targets() {
		std::string targets = "MakeMaker has found " + std::to_string(_listTarget.size()) + " targets."; 
		targets += "\n=================================";
		for(int i = 0; i < _listTarget.size(); i++) {
			targets += "\n" + std::string(_listTarget.at(i).get_title());
		}
		targets += "\n=================================";
		return targets;
	}

	std::string list_target(char* targetName) {
		Target* t = get_target_as_pointer(targetName);
		std::string target = std::string(t->get_title()) + ":";
		for(int i = 0; i < t->get_commands().size(); i++) {
			target += "\n" + std::to_string(i+1) + ":" + 
						std::string(t->get_commands().at(i).to_command());
		}
		return target;
	}

	std::string list_variables() {
		std::string variables = "";
		for (int i = 0; i < _listVariable.size(); i++) {
			variables += std::string(_listVariable.at(i).get_key()) + "=" + 
						 std::string(_listVariable.at(i).get_value()) + "\n";
		}
		return variables;
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

	Target get_target(int pos) {
		return _listTarget.at(pos);
	}

	std::vector<Target> get_targets() {
		return _listTarget;
	}

 private:
 	FileManager _file;
 	std::vector<Target> _listTarget;
 	std::vector<Variable> _listVariable;

 	Variable* get_variable(std::string v) {
 		for(int i = 0; i < _listVariable.size(); i++) {
 			if (!strcasecmp(v.c_str(), _listVariable.at(i).get_key())) {
 				return &_listVariable.at(i);
 			}
 		}
 		return NULL;
 	}

 	int get_variable_position(Variable v) {
 		for (int i = 0; i < _listVariable.size(); i++) {
 			if (v == _listVariable.at(i)) {
 				return i;
 			}
 		}
 		return -1;
 	}

 	bool check_variable_existence(Variable v) {
 		return get_variable_position(v) != -1;
 	}

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
