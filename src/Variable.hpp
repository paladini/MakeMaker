#ifndef VARIABLE_HPP__
#define VARIABLE_HPP__

#include <string>
#include "exceptions/VariableNullValue.hpp"

class Variable {
	
  public:
  	Variable(char* key, char* value) : _key(key), _value(value){}
    Variable(std::string keyPair) {
        int variableSeparator = keyPair.find_last_of("=");
        if (variableSeparator != -1) {
            std::string key = keyPair.substr(0, variableSeparator);
            std::string value = keyPair.substr(variableSeparator+1);

            if (value == "") {
                throw VariableNullValue();
            }

            char* tempKey = (char*) malloc (key.size()+1);
            char* tempValue = (char*) malloc (value.size()+1);
            memcpy(tempKey, key.c_str(), key.size()+1);
            memcpy(tempValue, value.c_str(), value.size()+1);

            set_key(tempKey);
            set_value(tempValue);
        }
    }
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
 	inline bool operator==(const Variable& rhs) const {return !(strcasecmp(this->_key,rhs._key));}
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