#ifndef TARGET_HPP_
#define TARGET_HPP_

#include <vector>
#include <string>
#include "Command.hpp"

class Target {

 public:
 	Target(std::string title) : _title(title) { } 

 	std::string getTitle() {
 		return _title;
 	}

 	std::vector<Command> getCommands() {
 		return _listCommand;
 	}

 private:
 	std::string _title;
 	std::vector<Command> _listCommand;

};
#endif