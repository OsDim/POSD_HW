#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;
#include <iostream>
#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
	List L;
	ASSERT_EQ("[]", L.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
	Number nb1(8128), nb2(496);
	vector<Term *> v = {&nb1, &nb2 };
	List L(v);
	ASSERT_EQ("[8128, 496]", L.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
	vector<Term *> v = {&terence_tao, &alan_mathison_turing };
	List L(v);
	ASSERT_EQ("[terence_tao, alan_mathison_turing]", L.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X"), Y("Y");
	vector<Term *> v = { &X, &Y };
	List L(v);
	ASSERT_EQ("[X, Y]", L.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom"), terence_tao("terence_tao");
	Number nb(496);
	Variable X("X");
	vector<Term *> v = { &nb, &X, &terence_tao };
	List L(v);
	ASSERT_FALSE(tom.match(L));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Atom terence_tao("terence_tao");
	Number nb1(496), nb2(8128);
	Variable X("X");
	vector<Term *> v = { &nb1, &X, &terence_tao };
	List L(v);
	ASSERT_FALSE(nb2.match(L));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Variable X("X");
	vector<Term *> v = { &X };
	Struct s(Atom("s"), v);

	Atom terence_tao("terence_tao");
	Number nb(496);
	vector<Term *> v2 = { &nb, &X, &terence_tao };
	List L(v2);

	ASSERT_FALSE(s.match(L));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Variable Y("Y");
	Atom terence_tao("terence_tao");
	Number nb(496);
	Variable X("X");
	vector<Term *> v = { &nb, &X, &terence_tao };
	List L(v);
	Y.match(L);
	ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Atom terence_tao("terence_tao");
	Number nb(496);
	Variable X("X");
	vector<Term *> v = { &nb, &X, &terence_tao };
	List L(v);

	ASSERT_TRUE(X.match(L));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Atom terence_tao("terence_tao");
	Number nb(496);
	Variable X("X");
	vector<Term *> v = { &nb, &X, &terence_tao };
	List L(v);

	ASSERT_TRUE(L.match(L));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Atom terence_tao("terence_tao");
	Number nb(496);
	Variable X("X"), Y("Y");
	vector<Term *> v1 = { &nb, &X, &terence_tao };
	List L1(v1);
	vector<Term *> v2 = { &nb, &Y, &terence_tao };
	List L2(v2);
	//std::cout << L2.symbol() << "\n";
	ASSERT_TRUE(L1.match(L2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Atom terence_tao("terence_tao");
	Number nb1(496), nb2(8128);
	Variable X("X");
	vector<Term *> v1 = { &nb1, &X, &terence_tao };
	List L1(v1);
	vector<Term *> v2 = { &nb1, &nb2, &terence_tao };
	List L2(v2);
	L1.match(L2);
	ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Variable Y("Y"), X("X");
	Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
	Number nb(496);
	vector<Term *> v = { &nb, &X, &terence_tao };
	List L(v);
	Y.match(L);
	X.match(alan_mathison_turing);
	ASSERT_EQ("alan_mathison_turing", X.value());
	EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args0 = { &f };
	List l1(args0);
	vector<Term *> args1 = { &l1, &s, &t };
	List l2(args1);

	EXPECT_EQ(string("[first]"), l2.head()->value());
	EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
	EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
	List L;
	ASSERT_EQ("Accessing head in an empty list", L.head()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
	List L;
	ASSERT_EQ("Accessing tail in an empty list", L.tail()->value());
}




#endif
