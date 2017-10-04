#include <list>
#include <iostream>
#include "include/Sort.h"

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {

	for (std::list<Shape*>::iterator list_iter = shapeList->begin();
		list_iter != shapeList->end(); list_iter++)
	{
		for (std::list<Shape*>::iterator list_iter2 = shapeList->begin();
			list_iter2 != shapeList->end(); list_iter2++)
		{
			if ((*list_iter)->perimeter() < (*list_iter2)->perimeter()) {
				std::swap(*list_iter, *list_iter2);
			}
		}
	}
}

 
void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	for (std::list<Shape*>::iterator list_iter = shapeList->begin();
		list_iter != shapeList->end(); list_iter++)
	{
		for (std::list<Shape*>::iterator list_iter2 = shapeList->begin();
			list_iter2 != shapeList->end(); list_iter2++)
		{
			if ((*list_iter)->perimeter() > (*list_iter2)->perimeter()) {
				std::swap(*list_iter, *list_iter2);
			}
		}
	}
}



void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
	/*
	std::cout << "\n";
	int i = 0;
	for (std::list<Shape*>::iterator list_it = shapeList->begin();
	list_it != shapeList->end(); list_it++)
	{
	std::cout << i << " : " << (*list_it)->area() << "\n";
	i++;
	}
	*/
	for (std::list<Shape*>::iterator list_iter = shapeList->begin();
		list_iter != shapeList->end(); list_iter++)
	{
		for (std::list<Shape*>::iterator list_iter2 = shapeList->begin();
			list_iter2 != shapeList->end(); list_iter2++)
		{
			if ((*list_iter)->area() < (*list_iter2)->area()) {
				std::swap(*list_iter, *list_iter2);
			}
		}
	}
	/*
	std::cout << "\n";
	i = 0;
	for (std::list<Shape*>::iterator list_it = shapeList->begin();
		list_it != shapeList->end(); list_it++)
	{
		std::cout << i << " : " << (*list_it)->area() << "\n";
		i++;
	}
	*/
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
	for (std::list<Shape*>::iterator list_iter = shapeList->begin();
		list_iter != shapeList->end(); list_iter++)
	{
		for (std::list<Shape*>::iterator list_iter2 = shapeList->begin();
			list_iter2 != shapeList->end(); list_iter2++)
		{
			if ((*list_iter)->area() > (*list_iter2)->area()) {
				std::swap(*list_iter, *list_iter2);
			}
		}
	}

}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
	// Compactness = area/perimeter
	/*
	std::cout << "\n";
	int i = 0;
	for (std::list<Shape*>::iterator list_it = shapeList->begin();
		list_it != shapeList->end(); list_it++)
	{
		std::cout << i << " : " << ((*list_it)->area() / (*list_it)->perimeter()) << "\n";
	i++;
	}
	*/
	for (std::list<Shape*>::iterator list_iter = shapeList->begin();
		list_iter != shapeList->end(); list_iter++)
	{
		for (std::list<Shape*>::iterator list_iter2 = shapeList->begin();
			list_iter2 != shapeList->end(); list_iter2++)
		{
			if ((*list_iter)->area() / (*list_iter)->perimeter() < (*list_iter2)->area() / (*list_iter2)->perimeter()) {
				std::swap(*list_iter, *list_iter2);
			}
		}
	}
	/*
	std::cout << "\n";
	i = 0;
	for (std::list<Shape*>::iterator list_it = shapeList->begin();
		list_it != shapeList->end(); list_it++)
	{
		std::cout << i << " : " << (*list_it)->area() / (*list_it)->perimeter() << "\n";
	i++;
	}
	*/
}
