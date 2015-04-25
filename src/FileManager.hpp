#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_
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
	 	}
	}
	 
	// TODO
	~FileManager() { }

	void write(std::string newContent) {
	 	std::ofstream makefile(_path.c_str());
	 	std::cout << newContent << std::endl;
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
	 
		
	std::string _path;
};
#endif
