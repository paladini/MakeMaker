#ifndef TARGET_HPP_
#define TARGET_HPP_

#include <vector>
#include <string>
#include <iostream>
#include "Command.hpp"

class Target {

 public:
 	// Target(std::string title) : _title(&title[0]) {} // "&title[0]" returns a char*
 	Target(std::string title) {
 		_title = (char*)title.c_str();
 	}
 	~Target() {} 
 	
 	void add_command (Command command) {
 		_listCommand.push_back(command);
 	}

 	void add_command (Command command, int line) {
 		int size = _listCommand.size();
 		if(size+1 < line) {
 			std::cout<<"The chosen target doesn't have that amount of commands." <<std::endl;
 			throw -1;
 		} else  if(size == 0 || (size+1) == line){
 			_listCommand.push_back(command);
 		} else {
 			_listCommand[line] = command;
 		}
 	}

 	std::vector<Command> get_commands() {
 		return _listCommand;
 	}

 	void set_title(char* title) {
 		_title = title;
 	}

 	char* get_title() {
 		return _title;
 	}

 private:
 	char* _title;
 	std::vector<Command> _listCommand;

};
#endif			