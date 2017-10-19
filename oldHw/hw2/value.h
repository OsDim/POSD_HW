#ifndef VALUE_H
#define VALUE_H

#include <string>
#include "number.h"
using std::string;

class Value{
public:
	Value(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  bool match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
    }
    return ret;
  }

private:
  string _value;
  bool _assignable = true;
};

#endif
