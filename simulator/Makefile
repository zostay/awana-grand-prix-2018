all: canon-sim lightbar-sim

canon-sim.o: canon-sim.c
	gcc -c -Wall -I/usr/local/include canon-sim.c -o canon-sim.o

lightbar-sim.o: lightbar-sim.c
	gcc -c -Wall -I/usr/local/include lightbar-sim.c -o lightbar-sim.o

canon-sim: canon-sim.o
	gcc -Wall -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives canon-sim.o -o canon-sim

lightbar-sim: lightbar-sim.o
	gcc -Wall -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives lightbar-sim.o -o lightbar-sim

clean:
	rm -f *.o canon-sim lightbar-sim
