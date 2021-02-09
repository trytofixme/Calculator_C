#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include "token.h"

#include "std_lib_facilities.h"

class Token_stream {             //реализация класса Token Stream
public:                          //для работы  с потоком лексем
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);        //функция, "съедающая" символы
private:                        //до определённого значения
	bool full;                  //включительно
	Token buffer;
};

const char name = 'a';
const char del = 'd';
const char let = 'L';
const char declkey = '#';
const char prompt = '>';
const char print = ';';
const char quit = 'q';
const char number = '8';
const char help = 'h';
const char sqr = 's';
const char c = 'c';
const char sci = 'S';
const char dot = '.';
const char lg = 'l';

const string input_file = "from";
const string output_file = "to";
const string sqroot = "sqrt";
const string helpful = "help";
const string ex = "exit";
const string constant = "const";
const string scient = "scientific";
const string logarifm = "log";
const string delt = "delete";

#endif