#ifndef FLAG_HPP_
#define FLAG_HPP_

#include <string>

class Flag {

 public:
 	Flag(std::string flag) {
 		_flagname = flag;
 	}

 	std::string getFlag() {
 		return _flagname;
 	}

 	void setFlag(std::string flag) {
 		_flagname = flag;
 	}


 private:
 	std::string _flagname;
};

#endif
