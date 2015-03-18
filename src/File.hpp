#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>

class File {

 public:
	File(std::string path) {
		_path = path;
	}
	~File(){ } 

	void setPath(std::string path) {
		_path = path;
	}

	std::string getPath() {
		return _path;
	}

 private:
	std::string _path;

}

#endif
