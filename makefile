all: hw6 #utAtom #utVariable  

hw6: main.o  
ifeq (${OS}, Windows_NT)
	g++ -o hw6 main.o -lgtest
else
	g++ -o hw6 main.o -lgtest -pthread
endif

main.o: main.cpp atom.h variable.h number.h term.h struct.h utVariable.h utStruct.h utList.h list.h global.h scanner.h parser.h utParser.h node.h
	g++ --std=gnu++0x -c main.cpp

utAtom: mainAtom.o
ifeq (${OS}, Windows_NT)
	g++ -o utAtom mainAtom.o -lgtest
else
	g++ -o utAtom mainAtom.o -lgtest -pthread
endif
mainAtom.o: mainAtom.cpp utAtom.h atom.h
	g++ --std=gnu++0x -c mainAtom.cpp

utVariable: mainVariable.o
ifeq (${OS}, Windows_NT)
	g++ -o utVariable mainVariable.o -lgtest
else
	g++ -o utVariable mainVariable.o -lgtest -pthread
endif	
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ --std=gnu++0x -c mainVariable.cpp

clean:
	rm -f *.o hw6 #utAtom #utVariable 
stat:
	wc *.h *.cpp