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

  private:
  	std::string _key;
  	std::string _value;

};
#endif