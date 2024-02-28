exe : tris.o f.o aff.o main.o 
	gcc -Wall tris.o f.o aff.o main.o -o exe 
	rm -f *.o
tris.o : structures.h tris.h tris.c
	gcc -Wall -c tris.c -o tris.o 
f.o : structures.h fonctions.h fonctions.c
	gcc -Wall -c fonctions.c -o f.o 
aff.o : structures.h affichage.h affichage.c
	gcc -Wall -c affichage.c -o aff.o 
main.o : main.c structures.h fonctions.h affichage.h
	gcc -Wall -c main.c -o main.o 