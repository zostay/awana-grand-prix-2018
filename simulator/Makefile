all: canon-sim

canon-sim.o: canon-sim.c
	gcc -c -Wall -I/usr/local/include canon-sim.c -o canon-sim.o

canon-sim: canon-sim.o
	gcc -Wall -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives canon-sim.o -o canon-sim

clean:
	rm -f *.o canon-sim
