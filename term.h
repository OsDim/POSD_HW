#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;
class Iterator;
class Term {
public:
	virtual string symbol() const = 0;
	virtual string value() const = 0;
	virtual string getClassName() const = 0;
	
	virtual Iterator * createIterator();
	
	virtual bool match(Term &term) {
		return symbol() == term.symbol();
	}
	virtual bool isAssignable(){};
  	virtual int arity(){};
  	virtual Term * args(int index){};
};

#endif