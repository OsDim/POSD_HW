#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Number {
public:
	Number(int s):_symbol(StringValueOf(s)), _value(StringValueOf(s)) {}

	string symbol() {
		return _symbol;
	}

	string value() {
		return _value;
	}

	string className() {
		return _className;
	}

	template <class T>
	bool match(T &atom) {
		if (atom.className() == "variable") {
			return atom.match(*this);
		}
		else {
			return	_value == atom.value();
		}
	}
		
	//bool operator ==(Number a) {return _symbol == a._symbol;}				
	
private:
	string _symbol;
	string _value;
	string _className = "number";
	string StringValueOf(int x) {
		stringstream ss;
		ss << x;
		return ss.str();
	}


};

#endif
