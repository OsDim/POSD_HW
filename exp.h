#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include "list.h"
#include <string.h>

using namespace std;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getExpressionResult( std::vector<string> & _s ) = 0;
};




class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }
  
  string getExpressionResult( std::vector<string> & _s ) {
	  
		if(evaluate()) {
			if( _left->symbol() == _right->symbol()) {
				if ( _s.empty() ) {
					_s.push_back("true") ;
				}
				
				return "true";
			}
			
			string out = _left->symbol() + " = " + _right->value() ;
			bool exit = false ;
			
			for (int i = 0 ; i < (int) _s.size() ; i++) {   //解決重複
			
				
			
				if ( _s[i] == out ) {
					out = "" ;
					exit = true ;
				}
			}
			if ( exit == false ) {
				
				_s.push_back(out) ;
			}
			
			return out ;
		}
		
		else {
			_s.push_back("false") ;
		  return "false";
		}
	}
  
	bool evaluate(){
		return _left->match(*_right);
	}

private:
  Term* _left;
  Term* _right;
};



class ConjExp : public Exp {
public:
	ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

	}
	string out ;
	
	string getExpressionResult( std::vector<string> & _s ){
		
		
		if ( strcmp( typeid(*_left).name() , "8MatchExp" ) == 0){  // ==
			
			MatchExp * me_if = dynamic_cast<MatchExp *> (_left) ;
			
			string temp = me_if->getExpressionResult(_s) ;
			
			
			if (temp == "true") {
				
			}
			else if (temp == "false") {
				out = temp ;
			}
			else if (temp == "") {
				out = out ;
			}
			else {
				if (out.size() == 0){
					out = temp ;
				}
				else {
					out = out + ", " + temp ;
				}
			}
			
			
		}
		
		
		else if ( strcmp( typeid(*_left).name() , "7ConjExp" ) == 0){ //
			
			out = out + _left->getExpressionResult(_s) ;
			
		}
		
		
		MatchExp * me = dynamic_cast<MatchExp *> (_right) ;
		
		string ooo = me->getExpressionResult(_s) ;
		
		if (ooo == "true") {
				
		}else if (ooo == "false") {
			
			
				out = ooo ;
			
			
		}else if (ooo == "") {
			
			out = out ;
			
		}
		else {
			if (out.size() == 0){
				out = ooo ;
			}
			else {
				out = out + ", " + ooo ;
			}
			
			
		}
		
		
		
		return out;
		
	}
  
  

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
};









class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }
  
	string out ;
	string getExpressionResult( std::vector<string> & _s ){  // 7DisjExp
		
		if ( strcmp( typeid(*_left).name() , "8MatchExp" ) == 0){  // ==
		
			string ooo = _left->getExpressionResult(_s) ;
			
			if (ooo == "true") {
					
			}else if (ooo == "false") {
				
				out = ooo ;
				
			}else if (ooo == "") {
				
				out = out ;
				
			}
			else {
				if (out.size() == 0){
					
					out = ooo ;
				}
				else {
					out = out + "; " + ooo ;
				}
			}
		
		}
		
		else if ( strcmp( typeid(*_left).name() , "7DisjExp" ) == 0){  //;
			
			string oo = _left->getExpressionResult(_s) ;
			out = oo + out ;
		}
		
		_s.clear() ;
		
		
		if ( strcmp( typeid(*_right).name() , "8MatchExp" ) == 0){  // ==
			
			string temp = _right->getExpressionResult(_s) ;
			
			out = out + "; " + temp ;
		}
		
		
		else if ( strcmp( typeid(*_right).name() , "7ConjExp" ) == 0){ //,
			
			string oo = _right->getExpressionResult(_s) ;
			
			if ( oo == "false" ) {
				if ( out.size() == 0) {
					out = oo ;
				}
			}
			else {
				out = out + "; " + oo ;
			}
		}
		return out;
		
	}
  
  

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
