#ifndef TARGET_HPP_
#define TARGET_HPP_

#include <vector>
#include <string>
#include "Command.hpp"

class Target {

 public:
 	Target(char* title) : _title(title) { } 

 	char* getTitle() {
 		return _title;
 	}

 	void addCommand(Command* command) {
 		_listCommand.push_back(*command);
 	}

 	void addCommand(Command* command, int line) {
 		int size = _listCommand.size();
 		if(size+1 < line) {
 			std::cout<<"The chosen target doesn't have that amout of commands." <<std::endl;
 			throw -1;
 		} else  if(size == 0 || (size+1) == line){
 			_listCommand.push_back(*command);
 		} else {
 			_listCommand[line] = *command;
 		}
 	}

 	std::vector<Command> getCommands() {
 		return _listCommand;
 	}

 	void setTitle(char* title) {
 		_title = title;
 	}

 private:
 	char* _title;
 	std::vector<Command> _listCommand;

};
#endif