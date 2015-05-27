#ifndef INSUFFICIENT_ARGUMENTS_HPP__
#define INSUFFICIENT_ARGUMENTS_HPP__
#include <iostream>
#include <exception>
using namespace std;

class InsufficientArguments : public exception {
  virtual const char* what() const throw() {
    return "Insufficient arguments was given, please run again with more arguments.";
  }
};
#endif