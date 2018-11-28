
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm -lgsl -lgslcblas

HEADERS = #initfcc.h alpotential.h
OBJECTS = #initfcc.o alpotential.o MD_main.o
PROGRAM = E3

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ E3.c $(CFLAGS) $(LIBS)

clean:
	rm -f *.o; rm -rf main;
	touch *.c

go :
	@./E3;


