#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <map>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;
using namespace std;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}
  
  bool isReDisj = false ;

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      l_it = _mapv.find(symtable[_scanner.tokenValue()].first);
      if(l_it==_mapv.end()){
        Variable * v =new Variable(symtable[_scanner.tokenValue()].first);
        _mapv.insert(std::pair<string,Variable*>(symtable[_scanner.tokenValue()].first,v));
        return v;
      }
      else
        return l_it->second;


    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
	_mapv.clear() ;
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
		isReDisj = false ;
      createTerm();
	  if(_scanner.currentChar() == '.')
       throw string("Unexpected ',' before '.'");
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
	else if(_currentToken == ';' && _scanner.currentChar()== '.'){
      throw string("Unexpected ';' before '.'");
    }
    else if(_currentToken == ',' && _scanner.currentChar()== '.'){
      throw string("Unexpected ',' before '.'");
    }
    else if(_currentToken == '.'){
      string msg = left->symbol() + " does never get assignment" ;
      throw string(msg);
    }
    else
      throw string("inputs don't follow the rule.");
  }
  
  string getExpressionResult(){
	std::vector<string> _s ;
	
	string o =  _expStack.top()->getExpressionResult( _s ) + ".";
	
	if (_s.empty()) {return "true." ;} //都true
	if ( (_s[0] == "true") && (_s.size() == 1) ) {return "true." ;} //都true
	else return o ;
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }
	
	string getResult(){
		vector<string> v;
		return _expStack.top()->getExpressionResult( v ) + ".";
	}
private:
  

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
	
	map<string,Variable*> _mapv;
  map<string,Variable*>::iterator l_it;
  
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
};
#endif
