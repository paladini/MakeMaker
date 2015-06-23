#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_
#include <iostream>
#include <fstream>
#include <vector>

class FileManager {
 public:
 	static FileManager* get_singleton(std::string path);

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
 	FileManager(){};  // Private so that it can  not be called
	FileManager(std::string path) {
		_path = path;
	 	if(!verify()){
	 		create();
	 	} else {
	 		_exists = true;
	 	}
	} 

    FileManager(FileManager const&){};             // copy constructor is private
    FileManager& operator=(FileManager const&){};  // assignment operator is private
    static FileManager* m_pInstance;

 
	bool verify() {
		std::ifstream makefile((&_path)->c_str());
  		return makefile.good();
	}
	 
	void create() {
	 	std::ofstream make;
  		make.open(_path.c_str());
  		make.close();
	}
	 
	bool _exists = false;
	std::string _path;
};

FileManager* FileManager::m_pInstance = NULL;
FileManager* FileManager::get_singleton(std::string path) {
   	if (!m_pInstance)   // Only allow one instance of class to be generated.
    	m_pInstance = new FileManager(path);
   	return m_pInstance;
}


#endif
