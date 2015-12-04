//gcc -o graphique graphique.c `sdl-config --cflags --libs` 
//./graphique



#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"





int graphique(int largeur_ecran, int hauteur_ecran, int marge, int larg_score)
{


	/*
	1 - Déclaration des variables
	
	SDL_Surface *ecran = NULL; 
	SDL_Surface *tank = NULL; 
	SDL_Surface *terrain = NULL;
	SDL_Surface *bandeau_score = NULL;
	SDL_Surface *mur = NULL;
	SDL_Rect positionTerrain;
	SDL_Rect positionScore;
	SDL_Rect positionMur;
	int longu_mur =100;
	int haut_mur = 5;
*/
	SDL_Event event;
	int continuer = 1;


	/*
	2 - SDL_Init : chargement de la SDL
	*/
	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
		{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
		exit(EXIT_FAILURE); // On quitte le programme
		}


	/*
	3 - Création d'une fenètre
	*/
	SDL_SetVideoMode(largeur_ecran+(3*marge)+larg_score, hauteur_ecran+(2*marge), 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE); // déf de la fenetre
	SDL_WM_SetCaption("Sirop bot", NULL); //titre de la fenetre
	//SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));


	/*
	4 - On s'occupe du terrain de jeu
	
	terrain=SDL_LoadBMP("sol.bmp");
	// On détermine la position du terrain
	positionTerrain.x = marge;
	positionTerrain.y = marge;
	// On blitte le terrain au bon endroit
	SDL_BlitSurface(terrain, NULL, ecran, &positionTerrain);
*/

	/*
	5 - On s'occupe du bandeau de score
	
	bandeau_score = SDL_CreateRGBSurface(0, larg_score, hauteur_ecran, 32, 255, 0, 0, 0);
	// On détermine la position du terrain
	positionScore.x = (2*marge)+largeur_ecran;
	positionScore.y = marge;
	// On blitte le terrain au bon endroit
	SDL_BlitSurface(bandeau_score, NULL, ecran, &positionScore);
*/

	/*
	5. On s'occupe du mur
	
	mur = SDL_CreateRGBSurface(0, longu_mur, haut_mur, 32, 0, 0, 0, 0);
	// On détermine la position du terrain
	positionMur.x = 10;
	positionMur.y = 10;
	// On blitte le terrain au bon endroit
	SDL_BlitSurface(mur, NULL, terrain, &positionMur);
*/



	/*
	5. La boucle principale
	*/
	while(continuer)
	{

		SDL_WaitEvent(&event);

		switch(event.type)
		{
			// En appuyant sur une echap, on quitte le programme
			case SDL_QUIT:
			continuer = 0;
			break;

			// En appuyant sur une touche, on quitte le programme
			case SDL_KEYDOWN:
			continuer = 0;
			break;
		}
		//SDL_Flip(ecran);
	}


	/*
	6. Pour terminer
	
	SDL_Flip(ecran);
	SDL_FreeSurface(terrain);
	SDL_FreeSurface(bandeau_score);
*/

	/*
	SDL_Quit : arrêt de la SDL
	*/
	SDL_Quit();

	return EXIT_SUCCESS;
}


int main (int argc, char *argv[])
{


graphique (800,800,20,200);



}


