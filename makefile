all: hw7

hw7: main.o atom.o global.h list.o parser.h scanner.h struct.h variable.h iterator.h
ifeq (${OS}, Windows_NT)
	g++ -o hw7 main.o -lgtest
else
	g++ -o hw7 main.o -lgtest -pthread
endif


main.o: main.cpp utIterator.h
	g++ --std=gnu++0x -c main.cpp
	
atom.o: atom.h atom.cpp
	g++ --std=gnu++0x -c atom.cpp
	
list.o: list.h list.cpp
	g++ --std=gnu++0x -c list.cpp



clean:
	rm -f *.o hw7
stat:
	wc *.h *.cpp