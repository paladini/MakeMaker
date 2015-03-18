#ifndef FLAG_HPP_
#define FLAG_HPP_
class Flag {

 public:
 	Flag(string flag) {
 		_flagname = flag;
 	}

 	string getFlag() {
 		return _flagname;
 	}

 	void setFlag(string flag) {
 		_flagname = flag;
 	}


 private:
 	string _flagname;
}