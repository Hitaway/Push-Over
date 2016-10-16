#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "partie1.h"
#include "partie2.h"
#include "partie3.h"

/*!
* Fonction allouant dynamiquement une partie et renvoyant l’adresse de celle-ci.
* La taille du plateau et les noms des joueurs sont saisis par l’utilisateur.
*
*/
partie * creerPartie ()
{
	int n=0;
	partie *pa;

	pa=malloc(sizeof (partie));
	pa->pionJoueurCourant=-1;
	if(NULL==pa)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}
	
	do
	{
	printf("Saisir n: ");
	scanf("%d", &n);
	}while(n<2 || n>8);			//Saisir n tant que n n'est pas compris entre 2 et 8 inclus
	pa->p = creerPlateau(n);
	
	pa->nomJoueur1 = malloc(128 * sizeof (char));
	if(NULL==pa->nomJoueur1)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}
	pa->nomJoueur2 = malloc(128 * sizeof (char));
	if(NULL==pa->nomJoueur2)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}
	
	printf("Saisir le nom du joueur 1: ");
	scanf("%127s", pa->nomJoueur1);
	printf("Saisir le nom du joueur 2: ");
	scanf("%127s", pa->nomJoueur2);
	return pa;
}

/*!
* Fonction désallouant dynamiquement la partie passée en paramètre
*
* \param pa : partie à désallouer
*/
void detruirePartie(partie * pa)
{
	assert( pa != NULL && "\n/§/  problème avec detruire plateau  /§/\n");
	free(pa->nomJoueur1);
	pa->nomJoueur1=NULL;
	free(pa->nomJoueur2);
	pa->nomJoueur2=NULL;
	detruitePalteau(pa->p);
	pa->p=NULL;
	free(pa);
	pa=NULL;
}

/*!
* Fonction changeant le pion du joueur courant (1 ou -1)
*
* \param pa : partie en cours
*/
void changePionJoueurCourant(partie * pa)
{ 
	pa->pionJoueurCourant = pa->pionJoueurCourant * -1;
}

/*!
* Fonction modifiant les variables ligne, col, di et dj passées en paramètre avec
* les valeurs saisies par l’utilisateur. Elle retourne 0 si le joueur a appuyé
* sur la lettre M et 1 sinon.
*
* \param p : partie
* \param ligne : ligne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
* \param col : colonne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
* \param di : direction d’insertion (ligne)
* \param dj : direction d’insertion (colonne)
*/
int saisieJoueur ( partie * pa, int * ligne, int * col, int * di, int * dj)
{
	char s[100];

	printf("Saisir la direction ou vous souhaitez inserez le pion et le numero de ligne ou colonne: ");
	scanf("%s", s);

	if(s[0]=='M')
		return 0;
	while(!(s[0]=='H' || s[0]=='B' || s[0]=='G' || s[0]=='D') || ((s[1]-48 < 1) || (s[1]-48 > pa->p->n)))
	{
		if(s[0]=='M')
			return 0;
		printf("Saisir une direction valide et un numero de ligne ou colonne valide: ");
		scanf("%s", s);
	}
	if(s[0]=='H')
	{
		*di=1;
		*dj=0;
		*col=s[1]-49;
		*ligne=0;
	}
	if(s[0]=='B')
	{
		*di=-1;
		*dj=0;
		*col=s[1]-49;
		*ligne=0;
	}
	if(s[0]=='G')
	{
		*di=0;
		*dj=1;
		*col=0;
		*ligne=s[1]-49;
	}
	if(s[0]=='D')
	{
		*di=0;
		*dj=-1;
		*col=0;
		*ligne=s[1]-49;
	}
	return 1;
}

/*!
* Fonction permettant au joueur courant de jouer.
* La fonction retourne 1 si le joueur joue, et 0 sinon (s’il appuie sur la touche M).
*
* \param pa : partie en cours
*/
int tourJoueurCourant(partie * pa)
{
	int ligne, col, di, dj;

	if(pa->pionJoueurCourant==-1)
		printf("C'est au tour de %s (jaune) de jouer\n", pa->nomJoueur1);
	else
		printf("C'est au tour de %s (rouge) de jouer\n", pa->nomJoueur2);

	do
	{
		if(saisieJoueur(pa, &ligne, &col, &di, &dj)==0)
			return 0;
		if(insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant)==0)
			printf("Placement Impossible\n");
	}while(insertionPionPossible(pa->p, ligne, col, di, dj, pa->pionJoueurCourant)==0);
	insertionPion(pa->p, ligne, col, di, dj, pa->pionJoueurCourant);
	affichage(pa->p);
	return 1;
}

/*!
* Fonction permettant de jouer à Push over.
*
* \param pa : pointeur sur une partie en cours (elle doit être allouée). La partie peut ne pas être
* un début de partie.
*
* Retourne 0 si un joueur veut accéder au menu principal, 1 si la partie s’est terminée normalement
* (Partie gagnée ou nulle)
*/
int jouer( partie * pa)
{
	do
	{
		if(tourJoueurCourant(pa)==0)
			return 0;
		changePionJoueurCourant(pa);
	}while(!(gagne(pa->p) == -1 || gagne(pa->p) == 1 || gagne(pa->p) == 2));
	return 0;
}
