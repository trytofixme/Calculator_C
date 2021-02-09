#include "symbol_table.h"
#include "errors.h"


double Symbol_table::get_value(string s)   //функция для получения значения
{                                            //по имени переменной
	for (int ind = 0; ind < constants.size(); ind++) {
		if (constants[ind].str == s) {
			return constants[ind].value;
		}
	}
	for (int ind = 0; ind < var_table.size(); ind++) {
		if (var_table[ind].str == s) {
			return var_table[ind].value;
		}
	}
	throw Undefined{};
}

void Symbol_table::set_value(string s, double d)//функция для присовения значений
{                                                 //имеющимся переменным 
	for (int ind = 0; ind < constants.size(); ind++) {
		if (constants[ind].str == s) {
			throw ConstError{};
		}
	}
	for (int ind = 0; ind < var_table.size(); ind++) {
		if (var_table[ind].str == s) {
			var_table[ind].value = d;
			return;
		}
	}
	throw Undefined{};
}

bool Symbol_table::is_declared(string s)//функция для проверки существования переменных
{
	for (int ind = 0; ind < constants.size(); ind++) {
		if (constants[ind].str == s) {
			throw ConstError{};
		}
	}
	for (int ind = 0; ind < var_table.size(); ind++) {
		if (var_table[ind].str == s) {
			return true;
		}
	}
	return false;
}

double Symbol_table::define_name(string s, double d)
{//функция для инициализации новых переменных
	if (is_declared(s)) {
		throw DeclarationError{};
	}
	if (buffer) {
		var_table[index].str = s;
		var_table[index].value = d;
		buffer = false;
		return d;
	}
	var_table.push_back(Variable(s, d));
	return d;
}

void Symbol_table::delete_name(string s)
{//функция для удаления пользовательских переменных
	if (!is_declared(s)) {
		throw DeclarationError{};
	}

	for (int ind = 0; ind < var_table.size(); ind++) {
		if (var_table[ind].str == s) {
			var_table[ind].str = "~";
			var_table[ind].value = 0;

			index = ind;
			buffer = true;
			return;
		}
	}

	return;
}

double Symbol_table::define_const(string s, double d)
{//функция для инициализации новых констант
	if (is_declared(s)) {
		throw DeclarationError{};
	}

	constants.push_back(Variable(s, d));
	return d;
}
