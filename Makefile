bld/c-sim.o: src/main.c
	gcc -c src/main.c -o bld/c-sim.o
	
all: bld/c-sim.o
	gcc bld/c-sim.o -o c-sim-exec
	
	
run: c-sim-exec
	./c-sim.exec
	
	
clean:
	rm -f bld/*