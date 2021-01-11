CC=gcc
CFLAGS= -g -Wall -std=c99 -c -fpic 
CLINK=$(CC)
CLIBS = -shared grades.o -o  libgrades.so
RM = rm -rf *.o 


libgrades.so: grades.o
	$(CLINK) $(CLIBS) -llinked-list -L.

grades.o: grades.c grades.h 
	$(CC) $(CFLAGS)  grades.c


clean:
	$(RM) libgrades.so