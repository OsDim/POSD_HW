#include "atom.h"
#include "variable.h"
#include "iterator.h"
#include <typeinfo>

//template<class T>
Iterator<Term*> * Term::createIterator(){
  return new NullIterator(this);
}
Iterator<Term*> * Term::createBFSIterator(){
  return new NullIterator(this);
}
Iterator<Term*> * Term::createDFSIterator(){
  return new NullIterator(this);
}


bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else
    return symbol() == a.symbol();
}
