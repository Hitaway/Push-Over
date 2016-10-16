#ifndef PARTIE2
#define PARTIE2
#include "partie1.h"

int indiceValide (plateau * p, int indice);
int caseValide(plateau * p, int indiceLigne, int indiceColonne);
int caseVide(plateau * p, int i, int j);
int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion);
void Echange(plateau * p, int *buf1, int * buf2, int j, int ligne, int InsertionEcorePossible);
void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion);
int gagne(plateau * p);

#endif
