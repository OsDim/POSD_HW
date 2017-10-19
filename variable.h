#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "term.h"
using std::string;
using std::cout;

class Variable:public Term{

public:

	Variable(string s):_symbol(s), _value(s){}

	string symbol() const { 
		return _symbol; 
	}

	string value() const {
		if (_nbMatched) {
			return _matchNb->symbol();
		}
		else {
			if (_varMatched) {
				return _aVar->value();
			}
		}
		return _value; 
	}

	string className() const {
		return _className;
	}
	/*
	bool nbMatched() {
		return _nbMatched;
	}*/

	bool match(Term &term) {
		bool ret = _assignable;
		if (_assignable) {

			if (term.className() == "number") {			
				if (!_nbMatched) {
					_matchNb = &term;
					if (_symbol == term.symbol()) {
						return true;
					}
					if (_varMatched) {
						if (_symbol != _aVar->symbol()) {//avoid loopcycle
							_aVar->match(term);
						}
					}
					_nbMatched = true;
					return true;
				}
				else {
					return 	_matchNb->match(term);
				}
			}

			if (term.className() == "variable"|| term.className() == "struct") {
				if (_varMatched) {
					_aVar->match(term);
					return true;
				}else{
					_aVar = &term;
					_value = term.symbol();
					if (_nbMatched) {
						term.match(*_matchNb);
					}
					_varMatched = true;
					return _varMatched;
				}
			}


			if (term.className() == "atom") {
				if (!_atomAssing) {
					if (_varMatched) {
						_aVar->match(term);
					}
					_value = term.symbol();
					_atomAssing = true;
					_varMatched = false;
				}
				else {
					return false;
				}
			}

		}
		_assignable = false;
		return ret;
	}

private:
	string _symbol;
	string _value;
	string _className = "variable";
	bool _assignable = true;
	bool _nbMatched = false;
	bool _varMatched = false;
	bool _atomAssing = false;
	Term * _matchNb;
	Term * _aVar;
};

#endif
