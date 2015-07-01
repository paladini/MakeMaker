#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_
#include <iostream>
#include <fstream>
#include <vector>

class FileManager {
 public:
 	static FileManager* get_singleton();

	void write(std::string newContent) {
		if (!_verified)
			throw -1;
	 	std::ofstream makefile(_path.c_str());
	 	if(makefile.is_open()) {
  			makefile << newContent;
  			makefile.close();
  			return;
  		} 
  		throw -1;
	}

	void set_path(std::string path) {
		_path = path;
	 	if(!verify()){
	 		create();
	 	} else {
	 		_exists = true;
	 	}
	}

	std::string read() {
		if (!_verified)
			throw -1;
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
 	FileManager(){};

    FileManager(FileManager const&){};
    FileManager& operator=(FileManager const&){};
    static FileManager* m_pInstance;

 
	bool verify() {
		std::ifstream makefile((&_path)->c_str());
		_verified = true;
  		return makefile.good();
	}
	 
	void create() {
	 	std::ofstream make;
  		make.open(_path.c_str());
  		make.close();
	}
	 
	bool _exists = false;
	bool _verified = false;
	std::string _path;
};

FileManager* FileManager::m_pInstance = NULL;
FileManager* FileManager::get_singleton() {
   	if (!m_pInstance)
    	m_pInstance = new FileManager;
   	return m_pInstance;
}


#endif
