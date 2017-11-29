#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "term.h"
using std::string;
using std::stringstream;

class Number:public Term {
public:
	Number(double v):_symbol(StringValueOf(v)), _value(StringValueOf(v)) {}

	string symbol() const {
		return _symbol;
	}

	string value() const {
		return _value;
	}

	string className() const {
		return _className;
	}

	template <class T>
	bool match(T &term) {
		if (term.className() == "variable") {
			return term.match(*this);
		}
		else {
			return	_value == term.value();
		}
	}
		
	//bool operator ==(Number a) {return _symbol == a._symbol;}				
	
private:
	string _symbol;
	string _value;
	string _className = "number";
	string StringValueOf(double x) {
		stringstream ss;
		ss << x;
		return ss.str();
	}


};

#endif
