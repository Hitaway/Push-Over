#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Couleur.h"
#include "partie1.h"

/*
* Fonction allouant dynamiquement un plateau dont l’adresse est retournée.
*
* \param n : taille d’un côté
*/
plateau* creerPlateau(int n)
{
	plateau *plateauJeu=malloc(sizeof (plateau));
	(*plateauJeu).n=n;
	(*plateauJeu).tableau = malloc((n*n)*sizeof(int));
	assert(n<=8 && n>=2 && "L'entier n doit être compris entre 2 et 8 inclus");
	
	int i;
	for(i=0; i<n*n; i++)
		*(plateauJeu->tableau+i)=0;
return plateauJeu;
}

/*
* Fonction désallouant dynamiquement le plateau passé en paramètre
*
* \param p : plateau à désallouer
*/
void detruitePalteau(plateau *p)
{
	assert( p != NULL && "\nproblème avec detruire plateau\n");
	free(p->tableau);	
	free(p);
	p=NULL;
}

/*
* Fonction retournant la valeur de la case (i,j) du plateau p
*
* \param p : plateau
* \param i : entier correspondant au numéro de ligne
* \param j : entier correspondant au numéro de colonne
*/
int getCase(plateau *p, int i, int j)
{
	assert(i>=0 && i<=(p->n));		//i indice de ligne
	assert(j>=0 && j<=(p->n));		//j indice de colonne
return p->tableau[(i * p->n) + j];
}

/*!
*
* Fonction modifiant la valeur de la case (i,j) du plateau p
*
* \param p : plateau
* \param i : entier compris entre [0,n-1]
* \param j : entier compris entre [0,n-1]
* \param valeur : entier compris entre [-1,1]
*/
void setCase(plateau *p, int i, int j, int val)
{
	assert(i>=0 && i<(p->n));		//i indice de ligne
	assert(j>=0 && j<(p->n));		//j indice de colonne
	assert(val>=-1 && val<=1);
	p->tableau[(i * p-> n) + j]=val;
}

void affiche_ligne_vide(plateau * p, int i, int j, int ligneMilieu)
{
	for(j=0; j < p->n ; j++)   //parcour case par case
	{
			if((i+j)%2==0)
			{
				if(getCase(p,i,j)==0 || ligneMilieu==1)		color_printf(WHITE, CYAN,"       ");
				if(getCase(p,i,j)==1 && ligneMilieu==0)		color_printf(RED, CYAN,"   #   ");
				if(getCase(p,i,j)==-1 && ligneMilieu==0)	color_printf(YELLOW, CYAN,"   #   ");
			}
			else
			{
				if(getCase(p,i,j)==0 || ligneMilieu==1) 	color_printf(WHITE, BLUE,"       ");
				if(getCase(p,i,j)==1 && ligneMilieu==0) 	color_printf(RED, BLUE,"   #   ");
				if(getCase(p,i,j)==-1 && ligneMilieu==0) 	color_printf(YELLOW, BLUE,"   #   ");
			}
	}
	printf("\n");
}

/*!
* Fonction affichant le plateau sur le terminal
*
* \param p : pointeur sur la partie que l’on souhaite afficher
*/
void affichage (plateau * p)
{
	clear_terminal();	//netoyer le terminal a chaque affiche
	int i, j;

	printf(" ");
	for(j=1; j <= p->n; j++)
		printf("   %d   ", j);
	printf("\n");
	for(i=0; i < p->n; i++)		//parcourir les lignes
	{
			printf(" ");
			affiche_ligne_vide(p, i, j, 1);
			printf("%d", i+1);	//afficher indice de ligne
			affiche_ligne_vide(p, i, j, 0);
			printf(" ");
			affiche_ligne_vide(p, i, j, 1);
	}
	printf("\n");
}
