#include <stdio.h>
#include "Couleur.h"
#include "partie1.h"
#include "partie2.h"
#include "partie3.h"
#include "partie4.h"

int main()
{
	clear_terminal();	//netoyer le terminal
	partie *pa = NULL;
	int choixMenu;
	do
	{
		choixMenu=menu(pa);
		if(choixMenu==1)
		{
			clear_terminal();
			pa = creerPartie();
			affichage(pa->p);
			jouer(pa);
		}
		if(choixMenu==2)
		{
			clear_terminal();
			pa = chargementPartie();
			affichage(pa->p);
			jouer(pa);
		}
		if(choixMenu==3)
		{
			clear_terminal();
			sauvegardePartie(pa);
		}
		if(choixMenu==4)
		{
			clear_terminal();
			affichage(pa->p);
			jouer(pa);
		}
		if(choixMenu==0)
		{
			detruirePartie(pa);
			return 0;
		}
	}while(gagne(pa->p)==0);
	if(gagne(pa->p) == -1)	printf("\t%s a gagner\n", pa->nomJoueur1);
	if(gagne(pa->p) == 1)	printf("\t%s a gagner\n", pa->nomJoueur2);
	if(gagne(pa->p) == 2)	printf("Match nul\n");
	detruirePartie(pa);
return 0;
}
