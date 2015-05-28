#ifndef OUTOFRANGE_EXCEPTION_HPP__
#define OUTOFRANGE_EXCEPTION_HPP__
#include <iostream>
#include <exception>
using namespace std;

class OutOfRangeException : public exception {
  virtual const char* what() const throw() {
  	return "Out of range exception! Please, provide a number inside the range.";
  }
};
#endif