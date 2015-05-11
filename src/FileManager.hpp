#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_
#include <iostream>
#include <fstream>
#include <vector>

class FileManager {

 public:
	FileManager() { }
	FileManager(std::string path) {
		_path = path;
	 	if(!verify()){
	 		create();
	 	} else {
	 		_exists = true;
	 	}
	} 
	 
	// TODO
	~FileManager() {
	}

	void write(std::string newContent) {
	 	std::ofstream makefile(_path.c_str());
	 	if(makefile.is_open()) {
  			makefile << newContent;
  			makefile.close();
  			return;
  		} 
  		throw -1;
	}

	std::string read() {
	 	std::string content;
	 	std::string line;
	 	std::ifstream makefile(_path.c_str());
 	 	if (makefile.is_open()) {
    		while (getline(makefile, line)) {
      			content += line + "\n";
    		}
    		makefile.close();
    		return content;
 		}
 		throw -1;
	}

	bool already_exists_a_makefile() {
		return _exists;
	}
	 
 private:
 
	bool verify() {
		std::ifstream makefile((&_path)->c_str());
  		return makefile;
	}
	 
	void create() {
	 	std::ofstream make;
  		make.open(_path.c_str());
  		make.close();
	}
	 
	bool _exists = false;
	std::string _path;
};
#endif
