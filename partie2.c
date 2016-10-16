#include <stdio.h>
#include "partie1.h"
#include "partie2.h"

/*!
* Fonction retournant 1 si l’indice est valide par rapport au plateau
*
* \param p : plateau
* \param indice : entier compris entre [0,n-1]
*/
int indiceValide (plateau * p, int indice) 
{
	if(p->n > indice)
		return 1;
	else
		return 0;
}

/*!
* Fonction retournant 1 si la case (indiceLigne,indiceColonne) existe sur le plateau
*
* \param p : plateau
* \param indiceLigne : entier correspondant à un indice de ligne
* \param indiceColonne : entier correspondant à un indice de colonne
*/
int caseValide(plateau * p, int indiceLigne, int indiceColonne) 
{
	if(indiceValide(p, indiceLigne) == 1 && indiceValide(p, indiceColonne) == 1)
		return 1;
	else
		return 0;
}

/*!
* Fonction retournant 1 si la case (i,j) du plateau p est vide
*
* \param p : plateau
* \param i : entier correspondant à un indice de ligne
* \param j : entier correspondant à un indice de colonne
*/
int caseVide(plateau * p, int i, int j)
{
	if(getCase(p,i,j)==1 || getCase(p,i,j)==-1)
		return 0;
	else
		return 1;
}

/*!
* Fonction retournant 1 si le pion peut être ajouté à partir de la case (ligne,col)
* dans la direction donnée par di,dj
*
* \param p : plateau
* \param ligne : ligne de la case où l’on insère le pion
* \param col : colonne de la case où l’on insère le pion
* \param di : direction sur les lignes
*
// -1 si l’on insère vers le haut,
*
// 0 si l’on reste sur la même ligne,
*
// 1 si l’on insère vers le bas
* \param dj : direction sur les colonnes
*
// -1 si l’on insère vers la gauche,
*
// 0 si l’on reste sur la même colonne,
*
// 1 si l’on insère vers la droite
* \param pion : 1 ou -1 suivant le joueur
*/
int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion)
{
	int j;
	int PlacementPossible=0;
	
	if(di == 0 && dj==1) //ligne horizontal vers la droite
	{
		for(j=0; j < p->n; j++)
		{
			if(caseVide(p, ligne, j) == 1 && (j != p->n-1))	PlacementPossible=1;	
			if((getCase(p, ligne, j)==pion || getCase(p, ligne, j)==0) && (j == p->n-1)) PlacementPossible=1;
		}
	}
	if(di == 0 && dj==-1) //ligne horizontal vers la gauche
	{
		for(j=p->n-1; j >= 0; j--)
		{
			if(caseVide(p, ligne, j) == 1 && (j != 0)) PlacementPossible=1;
			if((getCase(p, ligne, j)==pion || getCase(p, ligne, j)==0) && (j == 0)) PlacementPossible=1;
		}
	}
	if(di == 1 && dj==0) //Colone deplacement de haut en bas
	{
		for(j=0; j < p->n; j++)
		{
			if(caseVide(p, j, col) == 1 && (j != p->n-1)) PlacementPossible=1;
			if((getCase(p, j, col)==pion || getCase(p, j, col)==0) && (j == p->n-1)) PlacementPossible=1;
		}
	}
	if(di == -1 && dj==0) //Colone deplacement de bas en haut
	{
		for(j=p->n-1; j >= 0; j--)
		{
			if(caseVide(p, j, col) == 1 && (j != 0)) PlacementPossible=1;
			if((getCase(p, j, col)==pion || getCase(p, j, col)==0) && (j == 0)) PlacementPossible=1;
		}
	}
	return PlacementPossible;
}

/*!
* Fonction qui efectue l'echange des pions
* Cette fonction est utiliser plusieur fois dans InsertionPion
*
* \param p : plateau
* \param buf1 : variable de stockage temporaire
* \param buf2 : colonne de la case où l’on insère le pion
* \param j : colonne
* \param ligne : ligne
* \param InsertionEcorePossible : Une variable qui vaut Vrai ou Faux
*		dès que buf2 stocke 0 (donc une case vide) cela veut dire qu'il  
*		faut arrêter le decallage donc InsertionEcorePossible ce met a 0
*		et empecher ainssi apres de deplacer les pion.
*/
void Echange(plateau * p, int *buf1, int * buf2, int j, int ligne, int InsertionEcorePossible)
{
	if(*buf2==0)
		InsertionEcorePossible=0;
	if(InsertionEcorePossible==1)
	{
		*buf2=getCase(p, ligne, j);
		setCase(p, ligne, j, *buf1);
		*buf1=*buf2;
	}
}

/*!
* Fonction insérant le pion à partir de la case (ligne,col)
* dans la direction donnée par di,dj
*
* \param p : plateau
* \param ligne : ligne de la case où l’on insère le pion
* \param col : colonne de la case où l’on insère le pion
* \param di : direction sur les lignes
*
// -1 si l’on insère vers le haut,
*
// 0 si l’on reste sur la même ligne,
*
// 1 si l’on insère vers le haut
* \param dj : direction sur les colonnes
*
// -1 si l’on insère vers la gauche,
*
// 0 si l’on reste sur la même colonne,
*
// 1 si l’on insère vers la droite
* \param pion : 1 ou -1 suivant le joueur
*/
void insertionPion (plateau * p, int ligne, int col, int di, int dj, int pion)
{
	int buf1=pion;
	int buf2=1;
	int InsertionEcorePossible=1;
	int j;

	if(insertionPionPossible(p, ligne, col, di, dj, pion)==0)
		printf("Placement Impossible\n");
	else
	{
		if(di == 0 && dj==1) //ligne horizontal vers la droite
		{
			for(j=0; j < p->n; j++)		//CHAMGEMENT POSSIBLE j<p->n-1 en j<=p->n
				Echange(p, & buf1, & buf2, j, ligne, InsertionEcorePossible);
		}
		if(di == 0 && dj==-1) //ligne horizontal vers la gauche
		{
			for(j=p->n-1; j >= 0 ; j--)
				Echange(p, & buf1, & buf2, j, ligne, InsertionEcorePossible);
		}
		if(di == 1 && dj==0) //Colone deplacement de haut en bas
		{
			for(j=0; j < p->n; j++)
				Echange(p, & buf1, & buf2, col, j, InsertionEcorePossible);
		}
		if(di == -1 && dj==0) //Colone deplacement de bas en haut
		{
			for(j=p->n-1; j >= 0; j--)
				Echange(p, & buf1, & buf2, col, j, InsertionEcorePossible);
		}
	}
}

/*!
* Fonction retournant 1 ou -1 si l’un des joueurs a gagné, 2 si match nul et 0 si la partie
* n’est pas finie.
*
* \param p : plateau
*/
int gagne(plateau * p)
{
	int i, j;
	int lj1 =1;	//ligne joueur 1 (JAUNE	-1)
	int lj2 =1;	//ligne joueur 2 (ROUGE	 1)
	int cj1=1;	//colonne joueur 1
	int cj2=1;	//colonne joueur 2
	int ggJ1=0; //test si joueur 1 a gagner
	int ggJ2=0; //test si joueur 2 a gagner
	
	for(i=0; i < p->n; i++)		//parcourir les lignes
	{
		lj1 =1;
		lj2 =1;
		cj1 =1;
		cj2 =1;
		for(j=0; j < p->n ; j++)	//parcourir collone
		{
			if(getCase(p,i,j)==0 || getCase(p,i,j)==1 )	lj1=0;
			if(getCase(p,j,i)==0 || getCase(p,j,i)==1 ) cj1=0;
			if(getCase(p,i,j)==0 || getCase(p,i,j)==-1 ) lj2=0;
			if(getCase(p,j,i)==0 || getCase(p,j,i)==-1 ) cj2=0;
		}
		if(lj1 == 1 || cj1 == 1)  ggJ1=1;
		if(lj2 == 1 || cj2 == 1)  ggJ2=1;
	}
	if(ggJ1 == 1 && ggJ2 ==0 )	return -1;
	if(ggJ2 == 1 && ggJ1 ==0 )  return 1;
	if(ggJ1 == 1 && ggJ2 == 1)  return 2;
	return 0;
}
