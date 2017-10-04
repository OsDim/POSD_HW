#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s), _value(s) {}

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
		  return _value == atom.value();
	  }
  }
  //bool operator ==(Atom a) {return _symbol == a._symbol;}


private:
	string _symbol;
	string _value;
	string _className = "atom";
};

#endif
