#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_
#include <iostream>
#include <fstream>
#include <vector>

class FileManager {

 public:
	FileManager() { }
	FileManager(std::string path) {
		fileContent = new std::string[10000];
	 	_path = path;
	 	if(!verify()){
	 		create();
	 	} else {
	 		fileContent = read();
	 	}
	}
	 
	// TODO
	~FileManager() { }

	std::string* getFileContent() {
		return fileContent;
	}

	void write(std::string newContent) {
	 	std::ofstream makefile (_path.c_str());
	 	if(makefile.is_open()) {
  			makefile << newContent;
  			makefile.close();
  			return;
  		} 
  		throw -1;
	}

	std::string* read() {
	 	std::string content[10000];
	 	std::string line;
	 	std::ifstream makefile(_path.c_str());
	 	int i = 0;
 	 	if (makefile.is_open()) {
    		while (getline(makefile, line)) {
      			content[i] += line + "\n";
      			i++;
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
	 
	std::string fileContent[];
	std::string _path;
};
#endif
