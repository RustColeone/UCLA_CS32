CC = g32

all: Exe 

Exe : 

	echo "Compilation Starting"
	$(CC) -o evenlist.o evenlist.cpp
	$(CC) -o evenVector.o evenvector.cpp
	$(CC) -o badList.o badlist.cpp
	$(CC) -o badVector.o badvector.cpp
	$(CC) -o listAll.o listall.cpp
	$(CC) -o RunSequence.o Sequence.cpp runSequence.cpp
	g32fast -o sorts.o sorts.cpp

	./evenlist.o
	./evenVector.o
	./badList.o
	./badVector.o
	./listAll.o
	./RunSequence.o
	./sorts.o

	echo "All test complete and runned"

clean:
	rm *.o