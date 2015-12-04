//gcc -o main main.c `sdl-config --cflags --libs` 
//./main



#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"





int graphique(int largeur_ecran, int hauteur_ecran)
{


    /*
    1. Déclaration des variables
    */
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Surface *clotureVerticale = NULL, *clotureHorizontale = NULL;
    SDL_Event event;
    SDL_Rect positionZozor;
    SDL_Rect positionClotureGH, positionClotureD, positionClotureB;
    int continuer = 1;


    /*
    2. On s'occupe de la fenêtre
    */
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(largeur_ecran, hauteur_ecran, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //http://sdl.beuc.net/sdl.wiki/SDL_SetVideoMode
    SDL_WM_SetCaption("Sirop bot", NULL); //titre de la fenetre
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));//http://wiki.libsdl.org/SDL_FillRect




    /*
    3. Les clôtures
    */
    // On détermine les dimensions des clôtures verticales et horizontales
    clotureVerticale = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, ecran->h - 2*40, 32, 0, 0, 0, 0);
    clotureHorizontale = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w - 2*40, 10, 32, 0, 0, 0, 0);

    // On détermine la position des 4 clôtures
    // Celle de gauche et celle du haut (elles ont la même origine)
    positionClotureGH.x = 40;
    positionClotureGH.y = 40;
    // Celle de droite
    positionClotureD.x = ecran->w - 50;
    positionClotureD.y = 40;
    // Celle du bas
    positionClotureB.x = 40;
    positionClotureB.y = ecran->h -50;

    // On blitte les 4 clôtures aux bons endroits
    //Celle de gauche
    SDL_BlitSurface(clotureVerticale, NULL, ecran, &positionClotureGH);
    //Celle de droite
    SDL_BlitSurface(clotureVerticale, NULL, ecran, &positionClotureD);
    //Celle du haut
    SDL_BlitSurface(clotureHorizontale, NULL, ecran, &positionClotureGH);
    //Celle du bas
    SDL_BlitSurface(clotureHorizontale, NULL, ecran, &positionClotureB);


    /*
    4. Placement initial de Zozor
    */
    //On charge l'image de Zozor dans la surface et on rend le fond transparent
    zozor = SDL_LoadBMP("tank.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 255, 255, 255));

    // On rend le curseur invisible et on le centre (Zozor devient le curseur)
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse((ecran->w / 2 - zozor->w / 2), (ecran->h / 2 - zozor->h / 2));


    /*
    5. La boucle principale
    */
    while(continuer)
    {

        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            // En appuyant sur une touche, on quitte le programme
            case SDL_KEYDOWN:
                continuer = 0;
                break;

            // On limite les déplacements de Zozor à son enclos (mouahaha)
            case SDL_MOUSEMOTION:
            // Empêcher le dépassement vers la droite
                if(event.motion.x > ecran->w - zozor->w - 50)
                    SDL_WarpMouse(ecran->w - zozor->w - 50, event.motion.y);

            // Empêcher le dépassement vers la gauche
                if(event.motion.x < 50)
                    SDL_WarpMouse(50, event.motion.y);

            // Empêcher le dépassement vers le haut
                if(event.motion.y < 50)
                    SDL_WarpMouse(event.motion.x, 50);

            // Empêcher le dépassement vers le bas
                if(event.motion.y > ecran->h - zozor->h - 50)
                    SDL_WarpMouse(event.motion.x, ecran->h - zozor->h - 50);

                positionZozor.x = event.motion.x;
                positionZozor.y = event.motion.y;
                break;
        }

        // On efface et on blitte à nouveau toutes les surfaces aux éventuels nouveaux emplacements
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
        // Zozor
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        // Les clotures
        SDL_BlitSurface(clotureVerticale, NULL, ecran, &positionClotureGH);
        SDL_BlitSurface(clotureVerticale, NULL, ecran, &positionClotureD);
        SDL_BlitSurface(clotureHorizontale, NULL, ecran, &positionClotureGH);
        SDL_BlitSurface(clotureHorizontale, NULL, ecran, &positionClotureB);

        SDL_Flip(ecran);
    }


    /*
    6. Pour terminer
    */
    SDL_Flip(ecran);
    SDL_FreeSurface(zozor);
    SDL_FreeSurface(clotureVerticale);
    SDL_FreeSurface(clotureHorizontale);
    SDL_Quit();

    return EXIT_SUCCESS;
}


int main (int argc, char *argv[])
{


graphique (1024,800);



}


