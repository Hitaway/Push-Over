#include <stdio.h>
#include <stdlib.h>
#include "partie1.h"
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"
#include "Couleur.h"

/*!
* Fonction sauvegardant la partie passée en paramètre. Retourne 0 en cas de problème, 1 sinon.
*
*/
int sauvegardePartie( partie *pa)
{
	int i, j;
	
	FILE *f = fopen("sauvegarde.txt","wt");
	if(f == NULL)
	{
		printf ("Problème lors de l’ouverture du fichier\n");
		return 0;
	}
	fprintf(f ,"%d\n", pa->p->n);
	fprintf(f ,"%s\n", pa->nomJoueur1);
	fprintf(f ,"%s\n", pa->nomJoueur2);
	fprintf(f ,"%d\n", pa->pionJoueurCourant);
	for(i=0; i < pa->p->n; i++)		//parcourir les lignes
	{
		for(j=0; j < pa->p->n; j++)	//parcourir collone
		{
			fprintf(f ,"%d ", getCase(pa->p,i,j));
		}
		fprintf(f ,"\n");
	}
	fclose(f);
	return 1;
}

/*!
* Fonction chargeant la partie en cours. Retourne l’adresse de la partie nouvellement créée.
*
* Si aucune partie n’a été sauvegardée, une nouvelle partie est créée.
*/
partie * chargementPartie()
{
	partie *jeu;
	int i, j, buf, n;
	
	jeu=malloc(sizeof (partie));
	if(NULL==jeu)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}

	jeu->nomJoueur1 = malloc(128 * sizeof (char));
	if(NULL==jeu->nomJoueur1)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}
	jeu->nomJoueur2 = malloc(128 * sizeof (char));
	if(NULL==jeu->nomJoueur2)
	{
		printf("/!/ ERREUR D'ALLOCATION MEMOIRE /!/\n");
		exit(1);
	}

	FILE *f = fopen("sauvegarde.txt","rt");
	if(f == NULL)
	{
		printf ("Problème lors de l’ouverture du fichier\n");
		return 0;
	}
	fscanf(f ,"%d\n", &n);
	jeu->p = creerPlateau(n);
	jeu->p->n=n;
	fscanf(f ,"%s\n", jeu->nomJoueur1);
	fscanf(f ,"%s\n", jeu->nomJoueur2);
	fscanf(f ,"%d\n", &jeu->pionJoueurCourant);
	for(i=0; i < jeu->p->n; i++)		//parcourir les lignes
	{
		for(j=0; j < jeu->p->n; j++)	//parcourir collone
		{
			fscanf(f ,"%d ", &buf);
			setCase(jeu->p, i, j, buf); 
		}
	}
	fclose(f);
	return jeu;
}

/*!
* Fonction affichant le menu (si p!=NULL, on permet de reprendre une partie et de
* sauvegarder la partie)
*
* \param p : pointeur sur la partie courante.
* Valeur de retour :
*
0 si les joueurs veulent quitter le jeu,
*
1 s’ils veulent commencer une nouvelle partie,
*
2 s’ils veulent charger la dernière partie sauvegardée,
*
3 s’ils veulent sauvegarder la partie courante,
*
4 s’ils veulent reprendre la partie courante.
*/
int menu(partie *pa)
{
	int choix=0;
	clear_terminal();
	
   	printf("    ____             __       ____                   \n");
	printf("   / __ \\__ __ ____ / /_     / __ \\_   _____  _____\n");
	printf("  / /_/ / / / / ___/ __ \\   / / / / | / / _ \\/ ___/\n");
	printf(" / ____/ /_/ (__  ) / / /  / /_/ /| |/ /  __/ /      \n");
	printf("/_/    \\____/____/_/ /_/   \\____/ |___/\\___/_/    \n\n");
	if(!(pa==NULL))
	{
		printf("\t           MENU:\n");
		printf("\t3.Sauvegarder la partie courante\n");
		printf("\t4.Reprendre la partie courante\n");   
		printf("\t0.Quitter le jeu\n\n");
	   	printf("\tQuel est votre choix: ");
	   	scanf("%d", & choix);
	   	
		while(!(choix==0 || choix ==3 || choix ==4))
		{
			printf("Veuillez faire un choix: ");
		    scanf("%d", & choix);
		}
	}
	else
	{
		printf("\t           MENU:\n");
		printf("\t1.Commencer une nouvelle partie\n");
		printf("\t2.Charger la dernière partie sauvegardée\n");
		printf("\t3.Sauvegarder la partie courante\n");
		printf("\t4.Reprendre la partie courante\n");   
		printf("\t0.Quitter le jeu\n\n");
	   	printf("\tQuel est votre choix:");
	   	scanf("%d", & choix);
	   	
		while(!(choix==0 || choix==1 || choix==2 || choix==3 || choix==4))
		{
			printf("Veuillez faire un choix: ");
		    scanf("%d", & choix);
		}
	}  
	return choix;                	         
}
