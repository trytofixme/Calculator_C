#include "token_stream.h"
#include "std_lib_facilities.h"
#include "errors.h"

Token_stream::Token_stream() :
	full(false), buffer(0) {}

void Token_stream::putback(Token t)//������� ��� ����������� ������
{                                  //� ����� �����
	if (full) {
		throw FullBuffer{};
	}
	buffer = t;
	full = true;
}

Token Token_stream::get()          //������� ��� ���������� ������
{
	if (full) {                    //��������� ����� �� �������
		full = false;              //�������
		return buffer;
	}

	char ch;
	cin >> ch;
	if (cin.fail()) {
		cin.clear();
		cin.putback(print);
	}

	switch (ch) {                 //�������� ����������� ��� 
	case print:                   //�������� �������:   
	case '!':                     //���������� - ���� ����;
	case '^':                     //�������� ������� ������������
	case '%':                     //�����
	case '(': case ')':
	case '{': case '}':
	case '[': case ']':
	case '+':
	case '-':
	case '*':
	case '/':
	case '=':
	case ',':
		return Token(ch);
	case declkey:
		return Token(let);

	case '.':
		return Token(dot);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string str = " ";
			str = ch;
			while (cin.get(ch) &&
				(isalpha(ch) || isdigit(ch) || ch == '_')) {
				str += ch;
			}
			cin.putback(ch);
			if (str == ex) {
				return Token(quit);
			}
			if (str == helpful) {
				return Token(help);
			}
			if (str == sqroot) {
				return Token(sqr);
			}
			if (str == constant) {
				return Token(c);
			}
			if (str == scient) {
				return Token(sci);
			}
			if (str == logarifm) {
				return Token(lg);
			}
			if (str == delt) {
				return Token(del);
			}
			cin.putback(ch);
			return Token(name, str);
		}
		throw UnexpectedToken{ std::string("input char: ") + ch };
	}
}

void Token_stream::ignore(char c)
{
	if (full == true && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = '0';
	while (cin >> ch) {
		if (ch == c) {
			return;
		}
	}
}