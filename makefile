CC=gcc
CFLAGS=-Wall -g
CLINK=$(CC)


libgrades.so: grades.o
	gcc -shared grades.o -o  libgrades.so -llinked-list -L.

grades.o: grades.c grades.h 
	gcc -g -Wall  -std=c99 -c -fpic grades.c 


clean:
	