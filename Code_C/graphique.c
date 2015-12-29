//gcc -o graphique graphique.c `sdl-config --cflags --libs` 
//./graphique



#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"





int graphique(int largeur_ecran, int hauteur_ecran, int larg_score, int posix,int posiy)
{


	/*
	1 - Déclaration des variables
	*/
	SDL_Surface *ecran = NULL; 
	SDL_Surface *robot = NULL; 
	SDL_Surface *terrain = NULL;
	SDL_Surface *bandeau_score = NULL;
	SDL_Surface *mur = NULL;

	SDL_Event event;

	SDL_Rect positionTerrain;
	SDL_Rect positionRobot;
	SDL_Rect positionScore;
	SDL_Rect positionMur;

	int longu_mur =100;
	int haut_mur = 5;
	int marge =5;
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
	3 - Utilisation d'une icone de fenetre
	*/
	SDL_WM_SetIcon(SDL_LoadBMP("tank.bmp"), NULL);


	/*
	4 - Création d'une fenètre
	*/
	ecran = SDL_SetVideoMode(largeur_ecran, hauteur_ecran, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE); // définition de la fenetre
	if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
	{
		fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("Sirop bot", NULL); //titre de la fenetre
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 128, 128, 128)); //on colore l'ecran en gris


	/*
	5 - On s'occupe du terrain de jeu
	*/
	terrain=SDL_LoadBMP("sol.bmp");
	// On détermine la position du terrain
	positionTerrain.x = marge;
	positionTerrain.y = marge;


	/*
	6 - On s'occupe du robot
	*/
	robot=SDL_LoadBMP("Robot_jaune.bmp");
	//on rend le fond blanc de l'image transparent
	SDL_SetColorKey(robot, SDL_SRCCOLORKEY, SDL_MapRGB(robot->format, 255, 255, 255));
	// On détermine la position du terrain
	positionRobot.x = posix;
	positionRobot.y = posiy;



	/*
	7 - On s'occupe du bandeau de score
	*/
	bandeau_score = SDL_CreateRGBSurface(SDL_HWSURFACE, larg_score, hauteur_ecran, 32, 255, 0, 0, 0);
	SDL_FillRect(bandeau_score, NULL, SDL_MapRGB(bandeau_score->format, 102, 178, 255)); //on colore l'ecran en bleu
	// On détermine la position du terrain
	positionScore.x = largeur_ecran - larg_score -(2*marge);
	positionScore.y = marge;
	// On blitte le terrain au bon endroit
	SDL_BlitSurface(bandeau_score, NULL, ecran, &positionScore);




	/*
	5. On s'occupe du mur
	*/
	mur = SDL_CreateRGBSurface(0, longu_mur, haut_mur, 32, 0, 0, 0, 0);
	// On détermine la position du terrain
	positionMur.x = 10;
	positionMur.y = 10;
	// On blitte le terrain au bon endroit
	SDL_BlitSurface(mur, NULL, terrain, &positionMur);

	/*
	5 - On rafraichie
	*/
	SDL_Flip(ecran);




	// Activation de la répétition des touches
	SDL_EnableKeyRepeat(100, 100);



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
				switch(event.key.keysym.sym)
				{
				    case SDLK_ESCAPE:
					continuer = 0;
					break;
				    case SDLK_UP:
					positionRobot.y = positionRobot.y -5; 
					
					break;
				    case SDLK_DOWN:
					positionRobot.y = positionRobot.y +5; 
					
					break;
				    case SDLK_RIGHT:
					positionRobot.x = positionRobot.x +5; 
					
					break;
				    case SDLK_LEFT:
					positionRobot.x = positionRobot.x -5;
					
					break;
							
				}
			break;
		}
		// On affiche avec les nouvelles valeurs
		SDL_BlitSurface(terrain, NULL, ecran, &positionTerrain);
		SDL_BlitSurface(robot, NULL, ecran, &positionRobot);
		SDL_Flip(ecran);
	}
	


	/*
	6. Pour terminer
	*/
	SDL_Flip(ecran);
	SDL_FreeSurface(terrain);
	SDL_FreeSurface(bandeau_score);
	SDL_FreeSurface(robot);


	/*
	SDL_Quit : arrêt de la SDL
	*/
	SDL_Quit();

	return EXIT_SUCCESS;
}


int main (int argc, char *argv[])
{

	graphique (1100,800,200,40,40);


}


