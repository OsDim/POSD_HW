#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
using std::vector;

class Variable ;

class List : public Term {
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}

  string symbol() const ;

  string value() const ;

  string getClassName() const ;

  bool match(Term & term) ;

  Term * head() const;
  List * tail() const;

  Term * args(int index) {
    return _elements[index];
  }

  int arity() {return _elements.size();}

  Iterator * createIterator();
  Iterator * createBFSIterator();
  Iterator * createDFSIterator();

  bool isAssignable(){return true;}

private:
  vector<Term *> _elements;
  string const _className = "LIST_H";
};

#endif
