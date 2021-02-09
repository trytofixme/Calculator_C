#ifndef TOKEN
#define TOKEN

#include "std_lib_facilities.h"

class Token {                    //реализаци€ класса Token дл€
public:                          //считывани€ лексем
	char kind;
	double value;
	string strng;
	Token(char ch) :                          //перегрузка конструктора
		kind(ch), value(0), strng(" ") {}     //дл€ реализации хранени€
	Token(char ch, double val) :             //числовых и символьных 
		kind(ch), value(val), strng(" ") {}   //лексем
	Token(char ch, string name) :             //дл€ работы с именами
		kind(ch), value(0), strng(name) {}
};

#endif