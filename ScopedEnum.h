#pragma once
/**
SCOPED_ENUM declares a scoped enum with the following features
* use toString to get a string literal of the enum
* enum can only be used with full qualified name that allows the declaration of enums
  in the same scope with same enum values

the following declaration of the two enums causes an compiler error
enum e1 {
	A,
	B
}
enum e2 {
	A, // compiler error
	C
}

the following declaration of the two enums are allowed
SCOPED_ENUM(e1,
	A,
	B
);
SCOPED_ENUM(e2,
	A,
	C
);

usage simply delare like an enum
SCOPED_ENUM(eTest,
	A=1,
	B=3,
	C=5,
	D,
	EValue = 10,
	FValue
)

eTest e1 = eTest::EValue;
cout << e1.toString();
prints out EValue(10)
cout << e1;
prints out 10
*/

#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

/**
this is the base class of scoped_enum
it cannot be used direct only by the SCOPED_ENUM macro
*/
class ScopedEnum
{
protected:
	ScopedEnum()
	{
	}

	std::string &trim(std::string &s) const
	{
		s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
		return s;
	}

	std::string find(int e, const std::string& subject) const
	{
		std::tr1::regex r("(.+?)(,|$)+");
		std::string test(subject);
		int captures[] = { 1 };
		const std::tr1::sregex_token_iterator end;
		int ePos = 0;
		int eVal = -1;
		for (std::tr1::sregex_token_iterator iter(test.begin(), test.end(), r, captures); iter != end; ++iter) {
			std::string& t1 = iter->str();
			std::string name = trim(t1);

			if (t1.find("=") != std::string::npos) {
				name = trim(t1.substr(0, t1.find("=")));
				eVal = atoi(trim(t1.substr(t1.find("=") + 1)).c_str());
			}
			else
				eVal++;
			if (e == eVal) {
				std::stringstream ss;
				ss << name << "(" << eVal << ")";
				return ss.str();
			}
		}
		return "not found";
	}
};


#define SCOPED_ENUM(NAME, ...) \
class NAME: public ScopedEnum \
	{\
public:\
	enum __##NAME					{ __VA_ARGS__	};\
private:\
	__##NAME _e;\
public:\
	NAME()							{ }\
	NAME(const __##NAME& other)		{ _e = other; }\
	NAME(const NAME& other)			{ _e = other._e; }\
	std::string toString() const	{ return find(_e, #__VA_ARGS__); }\
	operator std::string() const	{ return find(_e, #__VA_ARGS__); }\
	operator int ()	const			{ return _e; }\
};