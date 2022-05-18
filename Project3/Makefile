CC = g32

all: Exe 

Exe : 

	echo "Compilation Starting"
	$(CC) -o test1.o Sequence.cpp test1.cpp
	echo "Compilation test1 Successful"
	$(CC) -o test2.o SequenceString.cpp testString.cpp
	echo "Compilation test2 Successful"
	$(CC) -o test3.o Sequence.cpp testLong.cpp
	echo "Compilation test3 Successful"
	./test1.o
	./test2.o
	./test3.o
	echo "All test complete and runned"

clean:
	rm *.o