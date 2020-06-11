all: solver

run:
	./solver

solver: clean lista.o grafo.o
	gcc -o solver lista.o grafo.o
	
grafo.o: grafo.c
	gcc -c grafo.c 
	
lista.o: lista.c
	gcc -c lista.c

clean:
	rm -f *.o solver
