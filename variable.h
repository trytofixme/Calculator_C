#ifndef VARIABLE
#define VARIABLE

#include "std_lib_facilities.h"

class Variable {                      //����� ��� ������ �
public:                               //�����������
	string str;
	double value;
	Variable(string n, double v):
		str(n), value(v){}
};

#endif