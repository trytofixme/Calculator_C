#ifndef VARIABLE
#define VARIABLE

#include "std_lib_facilities.h"

class Variable {                      //класс для работы с
public:                               //переменными
	string str;
	double value;
	Variable(string n, double v):
		str(n), value(v){}
};

#endif