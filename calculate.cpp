#include "calculate.h"

#include "std_lib_facilities.h"

#include "errors.h"
#include "token_stream.h"
#include "symbol_table.h"
#include "help.h"

unsigned factorial(double arg)      // ������� ��� ����������
{                                   //����������
	if (arg == 0) {
		return 1;
	}
	if (arg < 0) {
		throw NullNegative{};
	}
	if ((arg - int(arg)) != 0) {
		throw DoubleFact{};
	}

	return arg * factorial(arg - 1);
}

double expression(Token_stream& ts, Symbol_table& st);                //�������������� �����������

double primary(Token_stream& ts, Symbol_table& st)                    //�������������� ���������� ���
{                                   //��������� ���������
	Token t = ts.get();
	switch (t.kind) {
	case '-':                       //���������� ��� �������������
	{                               //�����
		double d = primary(ts, st);
		return -d;
	}
	case '+':                      //���������� ��� �������� �����
	{
		double d = primary(ts, st);
		return d;
	}
	case '(': case '{': case '[':  //���������� ��� ��������� � �������
	{
		double d = expression(ts, st);
		t = ts.get();
		if (t.kind != ')' && t.kind != '}' && t.kind != ']') {
			throw SmileError{};
		}
		return d;
	}
	case name:                    //��������� ����������
	{
		string var_name = t.strng;
		Token t = ts.get();
		if (t.kind != '=') {      //�������� ����������:
			ts.putback(t);        //�� �������� �� ��� �����������
			double d = st.get_value(var_name);
			return d;
		}
		double d = expression(ts, st);  //����������, ���� ��������
		st.set_value(var_name, d);
		throw NameGetSet{};
		return d;
	}
	case sqr:                     //���������� ��� ����������
	{                             //����������� �����
		Token t = ts.get();
		if (t.kind != '(' && t.kind != '{' && t.kind != '[') {
			throw SmileError{};
		}
		double d = expression(ts, st);
		if (d < 0) {
			throw NullNegative{};
		}
		t = ts.get();
		if (t.kind != ')' && t.kind != '}' && t.kind != ']') {
			throw SmileError{};
		}
		d = sqrt(d);
		return d;
	}
	case lg:
	{
		Token t = ts.get();
		if (t.kind != '(' && t.kind != '{' && t.kind != '[') {
			throw SmileError{};
		}
		double d1 = expression(ts, st);
		if (d1 <= 0 || d1 == 1) {
			throw NullNegative{};
		}
		t = ts.get();
		if (t.kind != ',') {
			throw SmileError{};
		}
		double d2 = expression(ts, st);
		if (d2 <= 0) {
			throw NullNegative{};
		}
		t = ts.get();
		if (t.kind != ')' && t.kind != '}' && t.kind != ']') {
			throw SmileError{};
		}
		d1 = log(d1);
		d2 = log(d2);
		double d = d2/d1;
		return d;
	}
	case number:                   //��������� �����
		return t.value;
	case dot:
		throw NullError{};
	default:
		throw PrimaryError{};
	}
}

double secondary(Token_stream& ts, Symbol_table& st) {                //�������������� ����������
	double left = primary(ts, st);        //��� �������������� �������
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '!':                   //���������� ��� ����������
		{                           //����������
			double d = factorial(left);
			left = d;
			t = ts.get();
			break;
		}
		case '^':                   //���������� ��� ����������
		{                           //� �������
			double d = primary(ts, st);
			if ((d - int(d)) != 0) {
				throw DoubleFact{};
			}
			left = pow(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term(Token_stream& ts, Symbol_table& st)                       //�������������� ���������� 
{                                   //��� �����
	double left = secondary(ts, st);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':                   //���������� ��� ���������
			left *= secondary(ts, st);
			t = ts.get();
			break;
		case '%':                   //���������� ��� ���������� 
		{                           //�������
			double d = secondary(ts, st);
			if (d == 0) {
				throw NullDivision{};
			}
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		case '/':                   //���������� ��� �������
		{
			double d = secondary(ts, st);
			if (d == 0) {
				throw NullDivision{};
			}
			left /= d;
			t = ts.get();
			break;
		}
		case '(':                  //���������� ��� ��������� � 
		{                          //����������� ������ '*'
			ts.putback(t);
			double d = secondary(ts, st);
			left *= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression(Token_stream& ts, Symbol_table& st)                //�������������� ���������� ��� ���������
{
	double left = term(ts, st);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':                  //���������� ��� ��������
			left += term(ts, st);
			t = ts.get();
			break;
		case '-':                  //���������� ��� ���������
			left -= term(ts, st);
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts, Symbol_table& st)               //������� ��� ����������
{                                  //� ������������� �����
	Token t = ts.get();            //���������������� ����������
	if (t.kind != name) {
		throw NameError{};
	}
	string var_name = t.strng;

	Token t2 = ts.get();
	if (t2.kind != '=') {
		throw NameError{};
	}

	double d = expression(ts, st);
	st.define_name(var_name, d);
	throw NameGetSet{};
	return d;
}

double const_declaration(Token_stream& ts, Symbol_table& st)        //������� ��� �������������
{                                 //���������������� ��������
	Token t = ts.get();
	if (t.kind != name) {
		throw NameError{};
	}
	string var_name = t.strng;

	Token t2 = ts.get();
	if (t2.kind != '=') {
		throw NameError{};
	}

	double d = expression(ts, st);
	st.define_const(var_name, d);
	throw NameGetSet{};
	return d;
}

double removing(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	if (t.kind != name) {
		throw NameError{};
	}

	st.delete_name(t.strng);
	throw NameGetSet{};

	return 0;
}

double statement(Token_stream& ts, Symbol_table& st)//�������-����������
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts, st);
	case c:
		return const_declaration(ts, st);
	case del:
		return removing(ts, st);
	default:
		ts.putback(t);
		return expression(ts, st);
	}
}

void clean_up_mess(Token_stream& ts)            //������� ��� ��������������
{                               //��������� ����� �����������
	ts.ignore(print);           //������
}

void calculate()                //������� ��� �������������
{                               //����������
	Token_stream ts;            //���������� ��� ����������
								//get() � putback()
	Symbol_table st;
	help_message();
	while (cin) {
		try {
			cout << prompt;     //����������� ��� �����
			Token t = ts.get(); //�������� ��������
			while (t.kind == print) {
				t = ts.get();
			}
			switch (t.kind) {
			case help:
				throw Help{};
				break;
			case quit:
				return;
			case sci:{
					double d = statement(ts, st);
					cout << scientific << d << endl;
					break;
				}
			default:{
					ts.putback(t);
					double d = statement(ts, st);
					cout << defaultfloat << d << endl;
				}
			}
		}
	
		catch (UnexpectedToken) {
			cout << "...Unexpected Token..." << endl;
			clean_up_mess(ts);
		}
		catch (FullBuffer) {
			cout << "...Full Token Stream Buffer..." << endl;
			clean_up_mess(ts);
		}
		catch (NullNegative) {
			cout << "...Negative value in sqrt/factorial/ln..." << endl;
			clean_up_mess(ts);
		}
		catch (DoubleFact) {
			cout << "...Expected integer numbers for factorial/sqrt/pow..." << endl;
			clean_up_mess(ts);
		}
		catch (SmileError) {
			cout << "...Expected ')' after expression..." << endl;
			clean_up_mess(ts);
		}
		catch (PrimaryError) {
			cout << "...Expected primary..." << endl;
			clean_up_mess(ts);
		}
		catch (NullDivision) {
			cout << "...Null Division..." << endl;
			clean_up_mess(ts);
		}
		catch (Undefined) {
			cout << "...Undefined variable..." << endl;
			clean_up_mess(ts);
		}
		catch (DeclarationError) {
			cout << "...Variable is declarated alredy...\n";
			clean_up_mess(ts);
		}
		catch (NameError) {
			cout << "...Inicialisation Error..." << endl;
			clean_up_mess(ts);
		}
		catch (ConstError) {
			cout << "...You can`t change const value..." << endl;
			clean_up_mess(ts);
		}
		catch (Help) {
			help_message();
		}
		catch (NameGetSet) {
			clean_up_mess(ts);
		}
		catch (NullError) {
			cout << "...Expected digit before dot..." << endl;
			clean_up_mess(ts);
		}
	}
}