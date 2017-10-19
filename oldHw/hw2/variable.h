#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }

  string className() {
	  return _className;
  }

  template <class T>
  bool match( T &atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom.symbol() ;
      _assignable = false;
	  return ret;
	}
	else {
		return _value == atom.value();
	}

  }

private:
  string _value;
  string _className = "variable";
  bool _assignable = true;
};

#endif
