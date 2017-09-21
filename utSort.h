#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <list>
#include <iostream>

const double epsilon = 0.000001;

TEST (Sort, sortByIncreasingPerimeter) {
	Circle cir3(0, 0, 6);
	Circle cir2(0, 0, 5);
	Circle cir1(0, 0, 4);
	Circle cir0(0, 0, 3);
	Circle cir4(0, 0, 2);
	std::list<Shape*> testList1;

	testList1.push_back(&cir0);
	testList1.push_back(&cir1);
	testList1.push_back(&cir2);
	testList1.push_back(&cir3);
	testList1.push_back(&cir4);
	Sort sort1;
	sort1.sortByIncreasingPerimeter(&testList1);
	ASSERT_NEAR(37.6991118, testList1.back() -> perimeter(), epsilon);
}

TEST (Sort, sortByDecreasingPerimeter) {
	Circle cir4(0, 0, 6);
	Circle cir3(0, 0, 5);
	Circle cir2(0, 0, 4);
	Circle cir1(0, 0, 3);
	Circle cir0(0, 0, 2);
	std::list<Shape*> testList2;

	testList2.push_back(&cir0);
	testList2.push_back(&cir1);
	testList2.push_back(&cir2);
	testList2.push_back(&cir3);
	testList2.push_back(&cir4);
	Sort sort2;
	sort2.sortByDecreasingPerimeter(&testList2);
	ASSERT_NEAR(37.6991118, testList2.front() -> perimeter(), epsilon);
}

TEST (Sort, sortByIncreasingArea) {
	Circle cir3(0, 0, 6);
	Circle cir2(0, 0, 5);
	Circle cir1(0, 0, 4);
	Circle cir0(0, 0, 3);
	Circle cir4(0, 0, 2);
	std::list<Shape*> testList3;

	testList3.push_back(&cir0);
	testList3.push_back(&cir1);
	testList3.push_back(&cir2);
	testList3.push_back(&cir3);
	testList3.push_back(&cir4);
	Sort sort3;
	sort3.sortByIncreasingArea(&testList3);
	ASSERT_NEAR(113.097335529, testList3.back() -> area(), epsilon);
}

TEST (Sort, sortByDecreasingArea) {
	Circle cir3(0, 0, 6);
	Circle cir2(0, 0, 5);
	Circle cir1(0, 0, 4);
	Circle cir0(0, 0, 3);
	Circle cir4(0, 0, 2);
	std::list<Shape*> testList4;

	testList4.push_back(&cir0);
	testList4.push_back(&cir1);
	testList4.push_back(&cir2);
	testList4.push_back(&cir3);
	testList4.push_back(&cir4);
	Sort sort4;
	sort4.sortByDecreasingArea(&testList4);
	ASSERT_NEAR(113.097335529, testList4.front()->area(), epsilon);
}

TEST (Sort, sortByIncreasingCompactness) {
	// Compactness = area/perimeter
	Circle cir3(0, 0, 6);
	Circle cir2(0, 0, 5);
	Circle cir1(0, 0, 4);
	Circle cir0(0, 0, 3);
	Circle cir4(0, 0, 2);
	std::list<Shape*> testList5;
	
	testList5.push_back(&cir0);
	testList5.push_back(&cir1);
	testList5.push_back(&cir2);
	testList5.push_back(&cir3);
	testList5.push_back(&cir4);
	Sort sort5;
	sort5.sortByIncreasingCompactness(&testList5);
	ASSERT_NEAR(3, testList5.back()->area() / testList5.back()->perimeter(), epsilon);
}

#endif
