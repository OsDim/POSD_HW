#ifndef NODE_H
#define NODE_H

#include "atom.h"
#include "variable.h"

#include <typeinfo>

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Operators payload;

  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate() {
	
    bool out = treeMaker() ;
	
	
	evaluate2() ;
    
    return out;
  }
  
  bool treeMaker() {
	
	if(payload==EQUALITY){
		
      return left->term->match(*(right->term));
    }
    else if ( payload == COMMA ) {
		
      return left->treeMaker() && right->treeMaker();
    }
	
	if ( payload == SEMICOLON ) {
      return left->treeMaker() && right->treeMaker();
    }
	
	
    return false;
	
  }
  
  
  void evaluate2() {
	if(payload == COMMA || payload == SEMICOLON){
		vector<Term *> sss;
		Node * n = this ;
		
		if(Struct * s = dynamic_cast<Struct*> (n->left->left->term)){
			for(int i = 0; i < (int) s->arity(); i++){
				sss.push_back(s->args(i)) ;
			}
		}
		else {
			sss.push_back(n->left->left->term) ;
		}
		
		if(Struct * s = dynamic_cast<Struct*> (n->left->right->term)){
			for(int i = 0; i < (int) s->arity(); i++){
				sss.push_back(s->args(i)) ;
			}
		}
		else {
			sss.push_back(n->left->right->term) ;
		}
		
		if (n->payload == SEMICOLON ) {
			sss.clear() ;
		}

		if (n->right->payload == COMMA ){
			
			sss.push_back(n->right->left->left->term) ;
			sss.push_back(n->right->left->right->term) ;
			sss.push_back(n->right->right->left->term) ;
			
			
			if(Struct * s = dynamic_cast<Struct*> (n->right->right->right->term)){
				if(Struct * ss = dynamic_cast<Struct*> (s->args(0))){
					sss.push_back(ss->args(0)) ;
				}
			}
			else {
				sss.push_back(n->right->right->right->term) ;
			}
		}
		else {
			sss.push_back(n->right->left->term) ;
			sss.push_back(n->right->right->term) ;
		}
		
		
			
			
		for ( int i = 0 ; i < sss.size() ; i++){
			for ( int j = 0 ; j < sss.size() ; j++){
				if( sss[i]->symbol() == sss[j]->symbol()){
					sss[i]->match( *(sss[j]) ) ;
				}
			}
			
		} 
	}
	
  }
  
  Term * term;
  Node * left;
  Node * right;
  
  
};

#endif
