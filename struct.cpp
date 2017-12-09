#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Iterator;
class Struct: public Term {
public:
  Struct(Atom name, vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }

  string symbol() const {
    if(_args.empty())
    return  _name.symbol() + "()";
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }

  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }

  string getClassName() const {
    return _className;
  }
  int arity() const {return _args.size();}
private:
  Atom _name;
  std::vector<Term *> _args;
  string const _className = "Struct";
};

#endif
