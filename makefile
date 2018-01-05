all: shell hw8


shell: shell.o atom.o list.o struct.o scanner.h parser.h exception.h
ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o atom.o list.o struct.o -lgtest
else
	g++ -o shell shell.o atom.o list.o struct.o -lgtest -lpthread
endif


hw8: mainExp.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o hw8 mainExp.o atom.o list.o struct.o -lgtest -lpthread
mainExp.o: mainExp.cpp expression.h scanner.h  atom.h struct.h variable.h   parser.h 
		g++ -std=c++11 -c mainExp.cpp

mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
	g++ -std=c++11 -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp
	
shell.o: shell.cpp scanner.h  atom.h struct.h variable.h parser.h
	g++ -std=gnu++0x -c shell.cpp

mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=c++11 -c mainVariable.cpp
list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp
#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h
		g++ -std=c++11 -c mainScanner.cpp
		
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=c++11 -c mainIterator.cpp


#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o utScanner hw8
stat:
	wc *.h *.cpp
