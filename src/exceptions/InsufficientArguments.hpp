#ifndef INSUFFICIENT_ARGUMENTS_HPP__
#define INSUFFICIENT_ARGUMENTS_HPP__
#include <exception>
#include <string>

using namespace std;

class InsufficientArguments : public exception {
  	public:
      InsufficientArguments(const string m="Insufficient arguments was given, please run again with more arguments."):msg(m){}
      ~InsufficientArguments(void){};
      const char* what(){return msg.c_str();}

	private:
       string msg;
};
#endif