
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm

HEADERS = initfcc.h alpotential.h
OBJECTS = initfcc.o alpotential.o MD_main.o
PROGRAM = MD

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o; rm -rf MD; rm -f energies.pdf; rm -f energy.dat;
	touch *.c

plot :
	@./MD; python plot_energies.py


