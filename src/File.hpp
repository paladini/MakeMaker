#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>

class File {

 public:
	File(std::string path) {
		_path = path;
	}
	~File(){ } 

	void set_path(std::string path) {
		_path = path;
	}

	std::string get_path() {
		return _path;
	}

 private:
	std::string _path;

};

#endif
