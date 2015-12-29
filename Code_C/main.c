//main.c  version 0.2 du 07/12/15

#include <stdio.h>
#include <math.h>
#include "robot_api.h"

//configuration simulateur
#define NB_ROBOT_MAX 10 	//Nombres de robots pouvant jouer (se connecter ????)
#define NB_MISSILE_ALLOWED 3 //nombre de missiles pouvant être tirées par robot
#define MISSILE_SPEED 2 //vitesse du missile en metres par seconde


//proto a deplacer
int creer_mur(s_mur* tab_mur,float Xdebut, float Ydebut, float Xfin, float Yfin);
void move_robot(s_robot* tab_robot, s_mur* tab_mur, int id, float speed, float angle);

void simu_missile_update(s_missile* tab_missile, s_robot* tab_robot);
void simu_missile_shoot(s_robot* tab_robot, int id, s_missile* tab_missile);

//variables globales
// A déplacer en define si possible
int LARGEUR_TERRAIN = 800; //largeur du terrain en metres
int HAUTEUR_TERRAIN = 600; //hauteur du terrain en metres
float RAYON_ROBOT = 0.02; //rayon du robot en metres

float MISSILE_LENGH = 0.01; //longueur du missile en mètres (utilsés pour position du missile)



int main()
{

int debug=0;


//déclaration des tableaux de mur, robot et missile
s_mur tab_mur[100] = {};
s_robot tab_robot[NB_ROBOT_MAX] = {};
s_missile tab_missile[NB_ROBOT_MAX*NB_MISSILE_ALLOWED] = {};

//initialisation des murs
creer_mur(tab_mur,0,0,0,HAUTEUR_TERRAIN);
creer_mur(tab_mur,0,HAUTEUR_TERRAIN,LARGEUR_TERRAIN,HAUTEUR_TERRAIN);
creer_mur(tab_mur,LARGEUR_TERRAIN,HAUTEUR_TERRAIN,LARGEUR_TERRAIN,0);
creer_mur(tab_mur,LARGEUR_TERRAIN,0,0,0);

//initialisation des robots
tab_robot[0].x = 40;
tab_robot[0].y = 40;
tab_robot[0].teta = 0.40;
tab_robot[0].life_point = 100;
tab_robot[0].existe = 1;
tab_robot[0].id_player = 1;
tab_robot[1].x = 500;
tab_robot[1].y = 450;
tab_robot[1].teta = 0.8;
tab_robot[1].life_point = 96;
tab_robot[1].existe = 1;
tab_robot[1].id_player = 2;

move_robot(tab_robot,tab_mur,1,7,- 5 * M_PI/6);
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
//printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
move_robot(tab_robot,tab_mur,0,10,M_PI/4);
//printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;

}
printf("Vie robot :%d\n",getlife(tab_robot,0));
printf("Vie robot :%d\n",getlife(tab_robot,1)); 
printf("missile pos : x = %f , y : %f\n",tab_missile[0].x, tab_missile[0].y);
printf("missile pos : x = %f , y : %f\n",tab_missile[1].x, tab_missile[1].y);

simu_missile_shoot(tab_robot, 0, tab_missile);
simu_missile_shoot(tab_robot, 1, tab_missile);
printf("missile pos : x = %f , y : %f\n",tab_missile[0].x, tab_missile[0].y);
printf("missile pos : x = %f , y : %f\n",tab_missile[1].x, tab_missile[1].y);
simu_missile_update(tab_missile, tab_robot);
printf("missile pos : x = %f , y : %f\n",tab_missile[0].x, tab_missile[0].y);
printf("missile pos : x = %f , y : %f\n",tab_missile[1].x, tab_missile[1].y);

return 1;
}


/*permet au robot de tirer un missile dans une direction donnée 
prend en parametre: 
    - l'angle de tir en radian (float) 
    - ne renvoie rien*/ 
void simu_missile_shoot(s_robot* tab_robot, int id, s_missile* tab_missile)
{

	if (tab_robot[id].nb_missile < NB_MISSILE_ALLOWED) //verif nb missiles tirés
	{
		int i=0;
		for (i=0; i < (NB_MISSILE_ALLOWED * NB_ROBOT_MAX);i++) //creation d'un nouveau missile dans premier element s_misile libre
		{
			if (tab_missile[i].existe == 0)
			{
printf("debug 1 ok");
				tab_missile[i].existe = 1; //creation du missile
				tab_missile[i].teta = tab_robot[id].teta;
				tab_missile[i].x = tab_robot[id].x + (RAYON_ROBOT + MISSILE_LENGH) * cos(tab_missile[i].teta);
				tab_missile[i].y = tab_robot[id].y + (RAYON_ROBOT + MISSILE_LENGH) * sin(tab_missile[i].teta);
				tab_missile[i].id_shooter = tab_robot[id].id_player;
	printf("missile pos : x = %f , y : %f\n",tab_missile[i].x, tab_missile[i].y);
			break;
			}
		}
	}
}

//gestion des missiles tirés pendant la simulation
void simu_missile_update(s_missile* tab_missile, s_robot* tab_robot)
{
	int i=0;
	for (i=0; i < (NB_ROBOT_MAX * NB_MISSILE_ALLOWED); i++)
	{
printf("i %d\n",i);
		if (tab_missile[i].existe)
		{		
			tab_missile[i].x = tab_missile[i].x + MISSILE_SPEED * cos(tab_missile[i].teta);
			tab_missile[i].y = tab_missile[i].y + MISSILE_SPEED * sin(tab_missile[i].teta);
		}
	}

	printf("pos x missile 0 = %f \n",tab_missile[0].x);
	printf("pos y missile 0 = %f \n",tab_missile[0].y);
	printf("pos x missile 1 = %f \n",tab_missile[1].x);
	printf("pos y missile 1 = %f \n",tab_missile[1].y);

}
/***************************Gestion collission à faire**************/

	



void move_robot(s_robot* tab_robot, s_mur* tab_mur, int id, float speed, float angle)
{
	float x_temp = tab_robot[id].x;
	float y_temp = tab_robot[id].y;
	x_temp += speed * cos(angle);
	y_temp += speed * sin(angle);
	
	//test des limites du terrain en x
	if (x_temp >= LARGEUR_TERRAIN)
		tab_robot[id].x = LARGEUR_TERRAIN;
	else if (x_temp <= 0)
				tab_robot[id].x = 0;
	else	
		tab_robot[id].x = x_temp;

	//test des limites du terrain en y	
	if (y_temp >= HAUTEUR_TERRAIN)
		tab_robot[id].y = HAUTEUR_TERRAIN;
	else if (y_temp <= 0)
		tab_robot[id].y = 0;
	else
		tab_robot[id].y = y_temp;

	tab_robot[id].teta = angle;
}

 /*permet de connaitre le niveau de vie d'un robot 
- pas de parametre 
- renvoie un entier qui représente le % de vie du robot (0-100)*/ 
int getlife(s_robot* tab_robot, int id)
{
	return tab_robot[id].life_point;
}

 

/* Création Mur */
int creer_mur(s_mur* tab_mur,float Xdebut, float Ydebut, float Xfin, float Yfin)
{
	//verification que la position des murs soient compris dans le terrain sinon retourne -1
	if ((Xdebut < 0 || Xdebut > LARGEUR_TERRAIN) || (Ydebut < 0 || Ydebut > HAUTEUR_TERRAIN) || (Xfin < 0 || Xfin > LARGEUR_TERRAIN) || (Yfin < 0 || Yfin > HAUTEUR_TERRAIN ))
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

