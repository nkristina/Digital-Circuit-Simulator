#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
#include <iostream>
using namespace std;

class Exception : public exception {
public:
	Exception(const char* msg) : exception(msg) {}
};

class WrongInput : public Exception {
public:
	WrongInput(const char* errorDesc) : Exception(errorDesc) {}
};

#endif // !_EXCEPTIONS_H_

