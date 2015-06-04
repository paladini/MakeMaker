#ifndef VARIABLE_HPP__
#define VARIABLE_HPP__

#include <string>
class Variable {
	
  public:
  	Variable(char* key, char* value) : _key(key), _value(value){}
  	~Variable(){}

  	void set_key(char* key) {
  		_key = key;
  	}

  	void set_value(char* value) {
		_value = value;
  	}

  	char* get_key() {
        return _key;
  	}

  	char* get_value() {
  		return _value;
  	}

  	// It's necessary implement this method this way because strcasecmp can return values < 0 or > 0 (e.g: 1,2,-2).
 	inline bool operator==(const Variable& rhs) const {return !(strcasecmp(this->_key,rhs._key)) && !(strcasecmp(this->_value, rhs._value));}
	inline bool operator!=(const Variable& rhs) const {return !(operator==(rhs));}
	inline bool operator< (const Variable& rhs) const {return this->_key < rhs._key;}
	inline bool operator> (const Variable& rhs) const {return this->_key > rhs._key;} 
	inline bool operator<=(const Variable& rhs) const {return !(operator> (rhs));}
	inline bool operator>=(const Variable& rhs) const {return !(operator< (rhs));}

  private:
  	char* _key;
    char* _value;

};
#endif