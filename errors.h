#ifndef ERROR
#define ERROR

#include <string>

class MyError
{
private:
	string message;
public:
	MyError( std::string msg)
		: message{ msg }
	{}

	string get_msg() const
	{
		return message;
	}
};

class UnexpectedToken : public MyError
{
public:
	UnexpectedToken( std::string msg )
		: MyError{ std::string("...Unexpected Token... :") + msg }
	{}
};
class FullBuffer{};
class NullNegative{};
class DoubleFact{};
class SmileError{};
class PrimaryError{};
class NullDivision{};
class Undefined{};
class DeclarationError{};
class NameError{};
class ConstError{};
class Help{};
class NameGetSet {};
class NullError {};

#endif