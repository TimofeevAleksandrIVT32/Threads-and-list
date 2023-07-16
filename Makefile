run:
	gcc -c main.c -o main.o
	gcc -c list.c -o list.o
	gcc -c threads.c -o threads.o
	gcc main.o list.o threads.o -o res -lpthread

clean:
	rm -f *.o res