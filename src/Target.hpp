#ifndef TARGET_HPP_
#define TARGET_HPP_

#include <list>
#include "Command.hpp"

class Target {

 public:
 	Target() { } 

 private:
 	std::list<Command> _listCommand;

};
#endif