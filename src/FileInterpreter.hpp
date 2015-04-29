#ifndef FILEINTERPRETER_HPP_
#define FILEINTERPRETER_HPP_
#include "Target.hpp"
#include "Command.hpp"
#include "File.hpp"
#include "FileManager.hpp"
#include <iostream>
#include <sstream>

class FileInterpreter {
 public:
	FileInterpreter (std::string path) : _manager(path) { }

	std::vector<Target> parseFile() {
		if(_manager.already_exists_a_makefile())
			return foundTargets(_manager.read());
		std::vector<Target> empty;
		return empty;
	}

 private:

 	FileManager _manager;

	std::vector<Target> foundTargets (std::string content) {
    	std::istringstream reader(content);
    	std::string line, newTargetName;
		std::vector<Target> targets;
		int pointsPosition, actual = 0;
    	//char* name; 
    	while (std::getline(reader, line)) {                                    // while there are lines to get in the content
    		pointsPosition = line.find_last_of(":");
    		if((line.at(0) != '\t') && (pointsPosition != -1)) {                // if the first character isn't a 'tab' and there are a colon in the line
    			newTargetName = line.substr(0, pointsPosition);
    			//name = (char*) malloc (newTargetName.size() + 1);
    			//memcpy(name, newTargetName.c_str(), newTargetName.size() + 1)
				targets.push_back(Target(&newTargetName[0]));              			 // the text of this line, excluding the colon, is a target
    		} else {
    			targets.at(actual).add_command(readCommand(line));               // otherwise, it is a command and we must parse this accurately
    			actual++;
    		}
    	}
    	return targets;
	}

	Command readCommand(std::string line) {
		int previousSpace, lastSpace, found = 0;
		Command command = Command();
		std::string text;
		std::vector<File> files;
		std::vector<Flag> flags;
		char ch = 'c';
		for(int i = 0; i < line.length(); i++) {                                // for each character in the line
			ch = line.at(i);
			if(ch == ' ' && ch != '\t') {                                       // if the actual character is a 'space' and isn't a 'tab',
				previousSpace = lastSpace;                                      // the previous space position is the last we found and
				lastSpace = i;                                                  // the last, now, is the actual character position.
				text = line.substr(previousSpace+1, lastSpace-previousSpace-1); // the text we want is the interval between the last space position plus last space position minus previous space position minus one
				if (line.at(previousSpace+1) != '-') {                          // if the character at previous space position plus one isn't a '-'
					files.push_back(File(text));                                // the text is a name of a file
					found++;

				// I've chagend the position of this two "else if" and "else".
				} else if (found == 0) {                                        // else, if we haven't found anything,
					command.set_compiler(Compiler(text.c_str()));                // the text is a compiler
					found++;
				} else {
					flags.push_back(Flag(text));                                // else, it's a flag
					found++;
				}
			} else if (line.length()-1 == i) {                                  // if it's the last character in the line, 
				text = line.substr(lastSpace+1, i - lastSpace);                 // the text we want is between the last space found plus one and the actual character   
				files.push_back(File(text));
				found++;
			}
		}
		command.add_files(files);
		command.add_flags(flags);
		return command;
	}
};
#endif