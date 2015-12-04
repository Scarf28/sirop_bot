#include <stdio.h>
#include <math.h>
#include "robot_api.h"



int creer_mur(s_mur* tab_mur,float Xdebut, float Ydebut, float Xfin, float Yfin);
void move_robot(s_robot* tab_robot, s_mur* tab_mur, int id, float speed, float angle);

//variables globales
int largeur_terrain = 800;
int hauteur_terrain = 600;

int main()
{


int debug=0;


//déclaration des tableaux de mur, robot et missile
s_mur tab_mur[100] = {};
s_robot tab_robot[10] = {};
s_missile tab_missile[30] = {};

//initialisation des murs
creer_mur(tab_mur,0,0,0,hauteur_terrain);
creer_mur(tab_mur,0,hauteur_terrain,largeur_terrain,hauteur_terrain);
creer_mur(tab_mur,largeur_terrain,hauteur_terrain,largeur_terrain,0);
creer_mur(tab_mur,largeur_terrain,0,0,0);

//initialisation des robots
tab_robot[0].x = 40;
tab_robot[0].y = 40;
tab_robot[0].teta = 0.40;
tab_robot[0].existe = 1;
tab_robot[1].x = 500;
tab_robot[1].y = 450;
tab_robot[1].teta = 0.8;
tab_robot[1].existe = 1;

move_robot(tab_robot,tab_mur,1,7,M_PI/2);
int i =0;
long int delay = 0;
/*
for (i=0; i<10;i++)
{
delay =0;


while(tab_robot[0].y < 100)
{


while (delay < 1000000000)
{
delay++;
}
move_robot(tab_robot,tab_mur,0,10,0.2);
}
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;

while(tab_robot[0].y >10)
{
move_robot(tab_robot,tab_mur,0,-10,0.2);
}
printf("robot pos :x= %f, y=%f, teta = %f\n",include <math.h> tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
}
*/
//printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
//printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[1].x,tab_robot[1].y,tab_robot[1].teta) ;
for (i=0; i<80;i++)
{
move_robot(tab_robot,tab_mur,0,10,M_PI/4);
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
move_robot(tab_robot,tab_mur,0,10,M_PI/4);
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
}


return 1;
}

void move_robot(s_robot* tab_robot, s_mur* tab_mur, int id, float speed, float angle)
{
	float x_temp = tab_robot[id].x;
	float y_temp = tab_robot[id].y;
	x_temp += speed * cos(angle);
	y_temp += speed * sin(angle);
	
	//test des limites du terrain en x
	if (x_temp >= largeur_terrain)
		tab_robot[id].x = largeur_terrain;
	else if (x_temp <= 0)
				tab_robot[id].x = 0;
	else	
		tab_robot[id].x = x_temp;

	//test des limites du terrain en y	
	if (y_temp >= hauteur_terrain)
		tab_robot[id].y = hauteur_terrain;
	else if (y_temp <= 0)
		tab_robot[id].y = 0;
	else
		tab_robot[id].y = y_temp;

	tab_robot[id].teta = angle;
}

/* Création Mur */
int creer_mur(s_mur* tab_mur,float Xdebut, float Ydebut, float Xfin, float Yfin)
{
	//verification que la position des murs soient compris dans le terrain sinon retourne -1
	if ((Xdebut < 0 || Xdebut > largeur_terrain) || (Ydebut < 0 || Ydebut > hauteur_terrain) || (Xfin < 0 || Xfin > largeur_terrain) || (Yfin < 0 || Yfin > hauteur_terrain ))
		return -1;
	else
	{
		int i = 0;
		//permet de completer la tab mur si d'autres murs existent
		while (tab_mur[i].existe !=0 && i <101)
		{
			i++;
		}
		//si plus de 100 murs, ajout impossible, retourne -2
		if (i > 100)
			return -2;

		tab_mur[i].Xdebut = Xdebut;
		tab_mur[i].Ydebut = Ydebut;
		tab_mur[i].Xfin = Xfin;
		tab_mur[i].Yfin = Yfin;
		tab_mur[i].existe = 1;
	}
return 1 ;
}



/* Affichage Mur */

