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

 	std::vector<Command> getCommands() {
 		return _listCommand;
 	}

 private:
 	char* _title;
 	std::vector<Command> _listCommand;

};
#endif