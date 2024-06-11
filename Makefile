prog : gestion.o main.o
	gcc -o prog gestion.o main.o

gestion.o : gestion.c gestion.o
	gcc -c gestion.c
	
main.c : main.c main.o
	gcc -c main.c
