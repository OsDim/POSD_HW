#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
using std::string;
using std::stack;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
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
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings(){
    while(_scanner.currentChar() != '.') {

      Term * term = createTerm();
	  
      if(Struct * s = dynamic_cast<Struct*> (term)){
		  //std::cout<<  "............" << std::endl ;
        bool exist =true ;
        Node * n = new Node(TERM, term, nullptr, nullptr);
		
        for(int i = 0; i < (int) s->arity(); i++){
          for(int j = 0; j < (int) temp_table.size(); j++){
			  //std::cout<<  s->args(i)->symbol() << "    " <<  temp_table[j]->term->symbol() << std::endl ;
            if(s->args(i)->symbol() == temp_table[j]->term->symbol()){
				std::cout<<  "inter" << std::endl ;
				
              s->args(i)->match(*(temp_table[j]->term));
			  //std::cout<<  s->args(i)->symbol() << "    " <<  temp_table[j]->term->symbol() << std::endl ;
              n = new Node(TERM, s->args(i), nullptr, nullptr);
              exist = false ;
            }
          }
        }
		
        if (exist){ 
          temp_table.push_back(n) ;
        }
		
      }

	  if ( term != nullptr ){
        _terms.push_back(term);
        Node * n = new Node(TERM, term, nullptr, nullptr);
        bool exist =true ;
		if( _scanner.currentChar() == ';' ) {
			temp_table.clear();
		}
			for( int i = 0 ; i < (int)temp_table.size() ;i++ ) {
			  if ( temp_table[i]->term->symbol() == n->term->symbol() ) {
				n = temp_table[i] ;
				_terms[_terms.size()-1] = n->term;
				exist = false ;
			  }
			}
		
        if (exist){ 
          temp_table.push_back(n) ;
        }
		
        op_term.push(n);
      }
      if( _scanner.currentChar() == '=' ) {


        Node * n = new Node(EQUALITY);
        op_op.push(n);
      }
      if( _scanner.currentChar() == ',' ) {
        Node * n = new Node(COMMA);
        Node * temp = makeTree();

        op_term.push(temp);

        op_op.push(n);
      }
	  
	  if( _scanner.currentChar() == ';' ) {
        Node * n = new Node(SEMICOLON);
        Node * temp = makeTree();

        op_term.push(temp);

        op_op.push(n);
      }
    }

    Node * temp ;

    while(op_op.size() > 0){
      temp = makeTree();
      op_term.push(temp);
      tree = temp;
    }
  }

  Node * makeTree() {
    Node * n = op_op.top();
    op_op.pop();
    n->right = op_term.top();
    op_term.pop();
    n->left = op_term.top();
    op_term.pop();

    return n;
  }

  Node * expressionTree(){
    return tree;
  }
  vector<Node *> temp_table;

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' ) {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node * tree;
  stack<Node*> op_term;
  stack<Node*> op_op;

};
#endif
