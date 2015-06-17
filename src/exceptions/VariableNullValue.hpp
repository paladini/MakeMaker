#ifndef VARIABLE_NULL_VALUE_HPP__
#define VARIABLE_NULL_VALUE_HPP__
#include <iostream>
#include <exception>
using namespace std;

class VariableNullValue : public exception {
  virtual const char* what() const throw() {
    return "Variable has a null value.";
  }
};
#endif