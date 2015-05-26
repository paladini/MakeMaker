#ifndef TARGET_HPP_
#define TARGET_HPP_

#include <vector>
#include <string>
// #include <string.h>
#include <iostream>
#include "Command.hpp"

class Target {

 public:
 	Target (char* title) : _title(title) {}
 	~Target() {} 
 	
 	void add_command (Command command) {
 		_listCommand.push_back(command);
 	}

 	void add_command (Command command, int line) {
 		int size = _listCommand.size();
 		if(size < line) {
 			std::cout<<"The chosen target doesn't have that amount of commands." <<std::endl;//TODO create an exception handler 
 			throw -1;
 		} else  if(size == 0){
 			_listCommand.push_back(command);
 		} else {
 			_listCommand[line] = command;
 		}
 	}

 	void remove_command(int line) {
 		if ((line >= 0) && (line <= _listCommand.size()))
 			_listCommand.erase(_listCommand.begin() + line);
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

 	// It's necessary implement this method this way because strcasecmp can return values < 0 or > 0 (e.g: 1,2,-2).
 	inline bool operator==(const Target& rhs) const {return !(strcasecmp(this->_title,rhs._title));}
	inline bool operator!=(const Target& rhs) const {return !(operator==(rhs));}
	inline bool operator< (const Target& rhs) const {return this->_title < rhs._title;}
	inline bool operator> (const Target& rhs) const {return this->_title > rhs._title;} 
	inline bool operator<=(const Target& rhs) const {return !(operator> (rhs));}
	inline bool operator>=(const Target& rhs) const {return !(operator< (rhs));}

 private:
 	char* _title;
 	std::vector<Command> _listCommand;

};
#endif			