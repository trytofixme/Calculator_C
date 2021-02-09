#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "std_lib_facilities.h"
#include "variable.h"

class Symbol_table {                         //класс для работы с константами
	vector<Variable> var_table;              //и пользовательскими переменными
	vector<Variable> constants = {            
		Variable("pi", 3.141592),
		Variable("e", 2.721828),
		Variable("k", 1000)
	};
	int index{ 0 };
	bool buffer{ false };
public:
	double get_value(string s);
	void set_value(string s, double d);
	bool is_declared(string s);
	double define_name(string s, double d);
	double define_const(string s, double d);
	void delete_name(string s);
};

#endif