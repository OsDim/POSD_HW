#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term {

public:
	virtual string symbol() const = 0;
	virtual string value() const = 0;
	virtual string className() const = 0;
	
	virtual bool match(Term &term) {
		return symbol() == term.symbol();
	}

};

#endif
