#ifndef PARTIE3
#define PARTIE3
#include "partie1.h"

typedef struct{
	char *nomJoueur1;
	char *nomJoueur2;
	int pionJoueurCourant;
	plateau * p;
}partie;

partie * creerPartie ();
void detruirePartie(partie * pa);
void changePionJoueurCourant(partie * pa);
int saisieJoueur ( partie * pa, int * ligne, int * col, int * di, int * dj);
int tourJoueurCourant(partie * pa);
int jouer( partie * pa);

#endif
