bld/c-sim.o: src/main.c
	gcc -c src/main.c -o bld/c-sim.o
	
setup:
	mkdir -p bld

all: setup bld/c-sim.o
	gcc bld/c-sim.o -o c-sim-exec
	
run: all
	./c-sim-exec
	
clean:
	rm -f bld/*