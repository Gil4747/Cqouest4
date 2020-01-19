all: main

main:
	gcc -Wall frequency.c -o frequency

clean:
	rm -f *.o frequency