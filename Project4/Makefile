CC = g32fast

all: Exe 

Exe : 

	echo "Compilation Starting"
	g32fast -o testerHash.o NameTablevhash.cpp testNameTable.cpp
	g32fast -o testerMap.o NameTablevmap.cpp testNameTable.cpp
	g32fast -o testerSlow.o NameTablevslow.cpp testNameTable.cpp

	./testerHash.o
	./testerMap.o
	./testerSlow.o

	echo "All test complete and runned"

clean:
	rm *.o