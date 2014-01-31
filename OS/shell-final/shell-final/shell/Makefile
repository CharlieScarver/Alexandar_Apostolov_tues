all: shell

shell.o: shell.c
	gcc -c shell.c

shell: shell.o
	gcc -o shell shell.o
	
clean:
	rm -f *.o *~ shell