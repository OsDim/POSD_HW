#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "atom.h"

#include <vector>
#include <iostream>
using std::vector;

class List : public Term {

public:

	List() : _elements() {}
	List(vector<Term *> elements) :_elements(elements), _notEmpty(true) {}

	string symbol() const {
		string s = "[";
		if (_notEmpty) {
			for (int i = 0; i < _elements.size() ; i++) {
				s += _elements[i]->symbol();
				if (i < _elements.size()-1) {
					s += ", ";
				}
			}
		}
		else {}
		s += "]";
		return	s;
	}

	string value() const {
		string s = "[";
		if (_notEmpty) {
			if (_elements[0]->value() == "empty") {
				return "Accessing tail in an empty list";
			}
			for (int i = 0; i < _elements.size(); i++) {
				s += _elements[i]->symbol();
				if (i < _elements.size() - 1) {
					s += ", ";
				}
			}
		}
		else {}
		s += "]";
		return	s;
	}

	string className() const {
		return _className;
	}

	Term * head() const {
		if (_notEmpty) {
			return _elements[0];
		}
		Atom *empty = new Atom("Accessing head in an empty list");
		return empty;
	};

	List * tail() const	{
		List *l;
		vector<Term *> tails;
		if (_notEmpty) {
			for (int i = 1; i<_elements.size(); i++) {
				tails.push_back(_elements[i]);
			}
			if (tails.size() != 0) {
				l = new List(tails);
			}
			else
			{
				l = new List();
			}
			return l;
		}
		Atom *temp = new Atom("empty");
		tails.push_back(temp);
		l = new List(tails);
		return l;
	};

	template <class T>
	bool match(T &term) {
		if (term.className() == "variable") {
			return term.match(*this);
		}
		else if (term.className() == "List") {
			if (_notEmpty) {
				List * mL = dynamic_cast<List *>(&term);
				for (int i = 0; i < _elements.size(); i++) {
					if (_elements[i]->value() != mL->_elements[i]->value()) {
						if (_elements[i]->className() != mL->_elements[i]->className()) {
							_elements[i]->match(* mL->_elements[i]);
							return false;
						}
					}
				}
			}
			return true;

		} else {
			return	_value == term.value();
		}
	}

private:
	vector<Term *> _elements;
	bool _notEmpty = false;
	string _value;
	string _className = "List";

};

#endif
