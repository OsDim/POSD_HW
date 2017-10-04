#ifndef UTTERM_H
#define UTTERM_H

#include "variable.h"
#include "atom.h"
#include "number.h"

//test Number.value()
TEST (Number, ctor) {
	Number ctor(25);
	ASSERT_EQ("25", ctor.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number testSymbol(25);
	ASSERT_EQ("25", testSymbol.symbol());
}
//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
	Number match01(25);
	Number match02(25);
	ASSERT_TRUE(match01.match(match02));
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
	Number match01(25);
	Number match02(0);
	ASSERT_FALSE(match01.match(match02));
}
//?- 25 = tom.
// false.
TEST (Number, matchFailureDiffConstant) {
	Number match01(25);
	Atom tom("tom");
	ASSERT_FALSE(match01.match(tom));
}
//?- 25 = X.
// true.
TEST (Number, matchSuccessToVar) {
	Number match01(25);
	Variable X("X");
	ASSERT_TRUE(match01.match(X));

}

//?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number nb0(25);
	ASSERT_FALSE(tom.match(nb0));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X("X");
	X.match(tom);
	ASSERT_EQ("tom", X.value());
}

// ?- X = tom, tom = X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Variable X("X");
	X.match(tom);
	tom.match(X);
	ASSERT_EQ("tom", X.value());
}

// ?- X = jerry, tom = X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Atom jerry("jerry");
	Variable X("X");
	X.match(jerry);
	ASSERT_FALSE(X.match(tom));
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
	Variable X("X");
	Number nb0(5);
	X.match(nb0);
	ASSERT_EQ("5", X.value());
}

// ?- X = 25, X = 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number nb0(25);
	Number nb1(100);
	X.match(nb0);
	ASSERT_FALSE(X.match(nb1));
}

// ?- X = tom, X = 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Number nb0(25);
	Atom tom("tom");
	X.match(tom);
	ASSERT_FALSE(X.match(nb0));
}
//?- tom = X, 25 = X.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
	Variable X("X");
	Number nb0(25);
	Atom tom("tom");
	tom.match(X);
	ASSERT_FALSE(nb0.match(X));
}
//?- X = tom, X = tom.
// true.
TEST(Variable, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	ASSERT_TRUE(X.match(tom));
}

#endif
