exe: main.o partie1.o partie2.o partie3.o partie4.o Couleur.o
	gcc -o exe main.o partie1.o partie2.o partie3.o partie4.o Couleur.o
	
main.o: main.c partie1.h partie2.h partie3.h partie4.h Couleur.h
	gcc -Wall -c main.c

partie1.o: partie1.c partie1.h Couleur.h
	gcc -Wall -c partie1.c
	
partie2.o: partie2.c partie2.h partie1.h Couleur.h
	gcc -Wall -c partie2.c
	
partie3.o: partie3.c partie3.h partie2.h partie1.h Couleur.h
	gcc -Wall -c partie3.c
	
partie4.o: partie4.c partie4.h partie3.h partie2.h partie1.h Couleur.h
	gcc -Wall -c partie4.c
	
Couleur.o: Couleur.c Couleur.h
	gcc -Wall -c Couleur.c
	
#clean sers a suprimer tout les fichier .o le exe et les autres 
#on execute clean avec: make clean
clean:
	rm -f ./*.o exe ./*~
