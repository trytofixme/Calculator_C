#ifndef TOKEN
#define TOKEN

#include "std_lib_facilities.h"

class Token {                    //���������� ������ Token ���
public:                          //���������� ������
	char kind;
	double value;
	string strng;
	Token(char ch) :                          //���������� ������������
		kind(ch), value(0), strng(" ") {}     //��� ���������� ��������
	Token(char ch, double val) :             //�������� � ���������� 
		kind(ch), value(val), strng(" ") {}   //������
	Token(char ch, string name) :             //��� ������ � �������
		kind(ch), value(0), strng(name) {}
};

#endif