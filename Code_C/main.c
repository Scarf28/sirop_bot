//main.c  version 0.2 du 07/12/15

#include <stdio.h>
#include <math.h>
#include "robot_api.h"

//configuration simulateur
#define NB_ROBOT_MAX 10 	//Nombres de robots pouvant jouer (se connecter ????)
#define NB_MISSILE_ALLOWED 3 //nombre de missiles pouvant être tirées par robot
#define MISSILE_SPEED 0.1 //vitesse du missile en metres par seconde
#define RAYON_ROBOT 0.2 //rayon du robot en metres

//proto a deplacer
int creer_mur(s_mur* tab_mur,float Xdebut, float Ydebut, float Xfin, float Yfin);
void move_robot(s_robot* tab_robot, int id, float speed, float teta);

void simu_missile_update(s_missile* tab_missile, s_robot* tab_robot);
void simu_missile_shoot(s_robot* tab_robot, int id, s_missile* tab_missile,float teta);
void simu_robot_update(s_robot* tab_robot, s_mur* tab_mur);

//variables globales
// A déplacer en define si possible
int LARGEUR_TERRAIN = 800; //largeur du terrain en metres
int HAUTEUR_TERRAIN = 600; //hauteur du terrain en metres


float MISSILE_LENGH = 0.1; //longueur du missile en mètres (utilsés pour position du missile)


/***************************************	MAIN	****************************************/
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
tab_robot[0].x = 100;
tab_robot[0].y = 100;
tab_robot[0].teta = M_PI/4;
tab_robot[0].life_point = 100;
tab_robot[0].existe = 1;
tab_robot[0].id_player = 1;
tab_robot[1].x = 101;
tab_robot[1].y = 101;
tab_robot[1].teta = -3*M_PI/4;
tab_robot[1].life_point = 96;
tab_robot[1].existe = 1;
tab_robot[1].id_player = 2;


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
/////////test position  robot
move_robot(tab_robot,0,0.1,M_PI/4);
move_robot(tab_robot,1,0.1,-3*M_PI/4);
/*
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[1].x,tab_robot[1].y,tab_robot[1].teta) ;
for (i=0; i<8;i++)
{
simu_robot_update(tab_robot, tab_mur);
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[0].x,tab_robot[0].y,tab_robot[0].teta) ;
printf("robot pos :x= %f, y=%f, teta = %f\n",tab_robot[1].x,tab_robot[1].y,tab_robot[1].teta) ;
}
*/
	
/////////test missile
simu_missile_shoot(tab_robot, 0, tab_missile,M_PI/4);
simu_missile_shoot(tab_robot, 1, tab_missile,M_PI);

printf("missile pos : x = %f , y : %f\n",tab_missile[0].x, tab_missile[0].y);
printf("missile pos : x = %f , y : %f\n",tab_missile[1].x, tab_missile[1].y);
for (i=0; i<8;i++)
simu_missile_update(tab_missile, tab_robot);
printf("missile pos : x = %f , y : %f\n",tab_missile[0].x, tab_missile[0].y);
printf("missile pos : x = %f , y : %f\n",tab_missile[1].x, tab_missile[1].y);

simu_missile_shoot(tab_robot, 0, tab_missile,M_PI/4);
simu_missile_shoot(tab_robot, 1, tab_missile,0);

for (i =0; i < (NB_ROBOT_MAX*NB_MISSILE_ALLOWED);i++)
{
printf("missile n°%d joueur: %d ,pos : x = %f , y : %f\n",i, tab_missile[i].id_shooter,tab_missile[i].x, tab_missile[i].y);
}
simu_missile_update(tab_missile, tab_robot);
simu_missile_update(tab_missile, tab_robot);
simu_missile_update(tab_missile, tab_robot);
for (i =0; i < (NB_ROBOT_MAX*NB_MISSILE_ALLOWED);i++)
{
printf("missile n°%d joueur: %d ,pos : x = %f , y : %f\n",i, tab_missile[i].id_shooter,tab_missile[i].x, tab_missile[i].y);																																																																																																																											
} 

return 1;
}
/***************************************	END MAIN	****************************************/

//gestion du déplacement des robots
void simu_robot_update(s_robot* tab_robot, s_mur* tab_mur)
{
	int i=0;
	int j=0;
	float x_temp=0;
	float y_temp=0;
	float pos_diff=0; 
	for (i=0; i < NB_ROBOT_MAX; i++)
	{
		if (tab_robot[i].existe ==1)
		{		
			x_temp = tab_robot[i].x + tab_robot[i].speed * cos(tab_robot[i].teta);
			y_temp = tab_robot[i].y + tab_robot[i].speed * sin(tab_robot[i].teta);

			//test des limites du terrain en x
			if (x_temp >= LARGEUR_TERRAIN - RAYON_ROBOT)
				tab_robot[i].x = LARGEUR_TERRAIN - RAYON_ROBOT;
			else if (x_temp <= 0)
				tab_robot[i].x = 0;
			else	
				tab_robot[i].x = x_temp;

			//test des limites du terrain en y	
			if (y_temp >= HAUTEUR_TERRAIN - RAYON_ROBOT)
				tab_robot[i].y = HAUTEUR_TERRAIN - RAYON_ROBOT;
			else  if (y_temp <= 0)
				tab_robot[i].y = 0;
			else
				tab_robot[i].y = y_temp;
		}
	}

/***************************Gestion collission à faire**************/
for (i=0; i < NB_ROBOT_MAX; i++)
{
	if (tab_robot[i].existe ==1)
	{
		for (j=0; j < NB_ROBOT_MAX; j++)
		{
			if ((tab_robot[j].existe == 1) && (i!=j))
			{
				pos_diff = sqrt(pow(tab_robot[i].x - tab_robot[j].x,2) + pow(tab_robot[i].y - tab_robot[j].y,2));
				if( pos_diff < RAYON_ROBOT)
				{
					//printf("if ok\n");
					//printf("diff x = %f\n",tab_robot[i].x - tab_robot[j].x);
					//printf("diff y = %f\n",tab_robot[i].y - tab_robot[j].y);
					printf("posdiff = %f\n",pos_diff);
					tab_robot[i].x -= ((RAYON_ROBOT-pos_diff)/2) * cos(tab_robot[i].teta);
					tab_robot[i].y -= ((RAYON_ROBOT-pos_diff)/2) * sin(tab_robot[i].teta);
					tab_robot[j].x -= ((RAYON_ROBOT-pos_diff)/2) * cos(tab_robot[j].teta);
					tab_robot[j].y -= ((RAYON_ROBOT-pos_diff)/2) * sin(tab_robot[j].teta);
				}
			}
		}
	}
}

}	


/*permet au robot de tirer un missile dans une direction donnée 
prend en parametre: 
    - l'angle de tir en radian (float) 
    - ne renvoie rien*/ 
void simu_missile_shoot(s_robot* tab_robot, int id, s_missile* tab_missile, float teta)
{

	if (tab_robot[id].nb_missile < NB_MISSILE_ALLOWED) //verif nb missiles tirés
	{
		int i=0;
		for (i=0; i < (NB_MISSILE_ALLOWED * NB_ROBOT_MAX);i++) //creation d'un nouveau missile dans premier element s_misile libre
		{
			if (tab_missile[i].existe == 0)
			{
				tab_missile[i].existe = 1; //creation du missile
				tab_robot[id].nb_missile++; //comptage des missiles tirés
				tab_missile[i].teta = teta;
printf("i = %d\n",i);
printf("teta missile = %f\n",teta);
				tab_missile[i].x = tab_robot[id].x + (RAYON_ROBOT + MISSILE_LENGH) * cos(tab_missile[i].teta);
printf("x = %f\n",tab_missile[i].x);
printf("cos = %f\n",cos(tab_missile[i].teta));
				tab_missile[i].y = tab_robot[id].y + (RAYON_ROBOT + MISSILE_LENGH) * sin(tab_missile[i].teta);
printf("y = %f\n",tab_missile[i].y);
printf("sin = %f\n",sin(tab_missile[i].teta));
				tab_missile[i].id_shooter = tab_robot[id].id_player;
				//printf("missile pos : x = %f , y : %f\n",tab_missile[i].x, tab_missile[i].y);
			break;
			}
		}
	}
}

//gestion des missiles tirés pendant la simulation
void simu_missile_update(s_missile* tab_missile, s_robot* tab_robot)
{
	int i=0;
	int j=0;
	float dist_mis_rob=0; //distance between a missile and a robot
	// Update missile position 
	for (i=0; i < (NB_ROBOT_MAX * NB_MISSILE_ALLOWED); i++)
	{
		if (tab_missile[i].existe !=0)
		{		
			tab_missile[i].x = tab_missile[i].x + MISSILE_SPEED * cos(tab_missile[i].teta);
			tab_missile[i].y = tab_missile[i].y + MISSILE_SPEED * sin(tab_missile[i].teta);
 
			/***************************Check collision between missile and robot**************/
			for (j = 0; j < NB_ROBOT_MAX;j++)
			{
				if (tab_robot[j].existe == 1)	//calcul de la distance entre le missile et le robot si le robot existe 
				{
					dist_mis_rob = sqrt(pow(tab_missile[i].x - tab_robot[j].x,2) + pow(tab_missile[i].y - tab_robot[j].y,2));
					if (dist_mis_rob < RAYON_ROBOT)	//robot touche par le missile
					{
						tab_missile[i].existe = 0; //Missile suppression
						tab_robot[j].life_point -= 10;
printf("robot %d a ete par le missile du joueur %d\n",j,tab_missile[i].id_shooter);
printf("vie du joueur %d = %d\n",j, tab_robot[j].life_point);
							if (tab_robot[j].life_point <= 0)	//Check Robot mort
							{
								tab_robot[j].existe = 0; //robot suppression
printf("robot %d mort !!!!!!!\n",j);
							}
					}
				}
			}
		}
	}

	//printf("pos x missile 0 = %f \n",tab_missile[0].x);
	//printf("pos y missile 0 = %f \n",tab_missile[0].y);
	//printf("pos x missile 1 = %f \n",tab_missile[1].x);
	//printf("pos y missile 1 = %f \n",tab_missile[1].y);




}
	



void move_robot(s_robot* tab_robot, int id, float speed, float teta)
{
	tab_robot[id].speed = speed;
	tab_robot[id].teta = teta;
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

