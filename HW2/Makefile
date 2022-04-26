CC = g32

all: Exe 

Exe : 

	echo "Compilation Starting"
	$(CC) -o test1 mazestack.cpp
	echo "Compilation test1 Successful"
	$(CC) -o test2 mazequeue.cpp
	echo "Compilation test2 Successful"
	$(CC) -o test3 eval.cpp
	echo "Compilation test3 Successful"

	./test1.o
	./test2.o
	./test3.o
	echo "All test complete and runned"

clean:
	rm *.o
