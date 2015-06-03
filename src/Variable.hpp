#idndef VARIABLE_HPP__
#define VARIABLE_HPP__

#include <string>
class Variable {
	
  public:
  	Variable(std::string key, std::string value) : _key(key), _value(value){}
  	~Variable(){}

  	void setKey(std::string key) {
  		_key = key;
  	}

  	void setValue(std::string value) {
		_value = value;
  	}

  	std::string getKey() {
  		return _key;
  	}

  	std::string getValue() {
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
  	std::string _key;
  	std::string _value;

};
#endif