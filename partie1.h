#ifndef PARTIE1
#define PARTIE1

typedef struct{
	int *tableau;
	int n;
}plateau;

plateau* creerPlateau(int n);
void detruitePalteau(plateau *p);
int getCase(plateau *p, int i, int j);
void setCase(plateau *p, int i, int j, int val);
void affiche_ligne_vide(plateau * p, int i, int j, int ligneMilieu);
void affichage (plateau * p);

#endif
