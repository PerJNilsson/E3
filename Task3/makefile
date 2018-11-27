
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm

HEADERS = #initfcc.h alpotential.h
OBJECTS = #initfcc.o alpotential.o MD_main.o
PROGRAM = main

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ main.c $(CFLAGS) $(LIBS)

clean:
	rm -f *.o; rm -rf main;
	touch *.c

plot :
	@./main;# python plot_energies.py


