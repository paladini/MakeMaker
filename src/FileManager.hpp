#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_
#include <iostream>
#include <fstream>

class FileManager {

 public:
	 FileManager() {}
	 FileManager(std::string path) {
	 	_path = path;
	 	if(!verify()){
	 		create();
	 	}
	 }
	 
	 // TODO
	 ~FileManager() {/*TODO*/}
	 void parse() { }
	 void update() { }
	 
	 // Colocar privado depois
	 void write(std::string newContent) {
	 	std::ofstream makefile (_path.c_str());
	 	if(makefile.is_open()) {
  			makefile << newContent;
  			makefile.close();
  			return;
  		} 
  		throw -1;
	 }
	 
 private:
	
	std::string _path;
 
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
	

	 
	 bool verify() {
		std::ifstream makefile((&_path)->c_str());
  		return makefile;
	 }
	 
	 void create() {
	 	std::ofstream make;
  		make.open(_path.c_str());
  		make.close();
	 }
	 
	
};
#endif
