#ifndef HELP
#define HELP

#include "std_lib_facilities.h"

void help_message()
{
	cout << endl;
	cout << "INSTRUCTION: " << endl << endl;
	cout << "- use '+' to add;" << endl;
	cout << "- use '-' to substract;" << endl;
	cout << "- use '*' to multiply;" << endl;
	cout << "- use '/' to devide;" << endl;
	cout << "- use '%' to find remainder;" << endl;
	cout << "- use '!' to find factorial;" << endl;
	cout << "- use '^' to find degree;" << endl;
	cout << "- use '#' to inicialize variable;" << endl;
	cout << "- use 'const' to define your own constant;" << endl;
	cout << "- use 'delete' do delete your own variable;" << endl;
	cout << "- use sqrt () to find square root;" << endl;
	cout << "- use log (d1, d2) to find d2 log with d1 - foundation;\n";
	cout << "- use ';' to print result;" << endl;
	cout << "You can use standart math constand." << endl;
	cout << "-----------------------------------" << endl;
	cout << "Enter 'scientific' if you want calculator to ";
	cout << "print numbers in scientific form;" << endl;
	cout << "Enter 'help' to see instruction." << endl;
	cout << "Enter 'exit' to exit." << endl << endl;
}

#endif