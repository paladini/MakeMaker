#ifndef SOMETHINGWRONG_EXCEPTION_HPP__
#define SOMETHINGWRONG_EXCEPTION_HPP__
#include <iostream>
#include <exception>
using namespace std;

class SomethingWrongException : public exception {
  virtual const char* what() const throw() {
  	return "Something wrong happened, I think that capivaras are eating our software.";
  }
};
#endif