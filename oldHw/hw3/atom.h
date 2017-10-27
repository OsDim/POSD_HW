#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;


class Atom : public Term{

public:
	Atom (string s):_symbol(s), _value(s) {}

	string symbol() const{
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

private:
	string _symbol;
	string _value;
	string _className = "atom";

};


#endif
