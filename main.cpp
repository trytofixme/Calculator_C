#include <clocale>
#include "std_lib_facilities.h"
#include "calculate.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	try {
		calculate();
		return 0;
	}
	catch (...) {
		cerr << "exception\n";
		keep_window_open();
		return 2;
	}
}