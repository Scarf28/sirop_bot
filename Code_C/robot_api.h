// robot_api.h
/* liste des fonctions pour le simulateur*/


#ifndef ROBOT_API_H
#define ROBOT_API_H

#include <stdio.h>

//definition des structures
struct s_robot{
	float x;	//position x en metre du centre du robot
	float y;	//position y en metre du cnetre du robot
	float teta;	//angle en radian (entre 0 et 2pi)
	int existe; //0 = pas de robot; 1 = robot présent
};

struct s_missile{
    float x;    //position x en metre en tête du missile
    float y;    //position y en metre en tête du missile
    float teta; //angle relatif du missile pas rapport à l'axe x en radian
    int existe; //0 = pas de missile; 1 = missile présent
}

//definit les points de depart et de fin du mur Xdebut, Ydebut Xfin, Yfin  en float
//ainsi qu'un entier qui nous renseigne sur la présence du mur (0 = pas de mur; 1 = mur présent)
struct s_mur{
    float Xdebut;
    float Ydebut;
    float Xfin;
    float Yfin;
    int existe;
}

float scanlight[8] = [0 0 0 0 0 0 0 0]; // tableau correspondant au scan light pour les 8 zones

struct scanfin{
    float dist_scan[10] = [0 0 0 0 0 0 0 0 0 0]; // les 10 distances les plus courtes pour le scan selectionnée
    int type_scan[10] = {}; //type d'objet scanné sur la zone scannée
}


/*Initialisation des connexions TCP/IP
prend en paramètre :
	- un nom de robot
	- l'adresse ip du serveur pour la connexion
	- le port pour la connexion
renvoie id du joueur, renvoie -1 si problème de connexion, code d'erreur à préciser par la suite*/
int init_connexion(char[40] nom, char[15] ip, int port);

/*permet de récupérer la position d'un robot:
pas de parametre
renvoie une structure robot*/
robot get_position();

/*permet de demander de déplacer un robot
prend en parametre :
    - la vitesse du robot (speed) en m/s
    - la direction du robot en radian
ne renvoie rien*/
void move(float speed, float teta);

/*permet de connaitre l'etat du robot, pour savoir si il touche un objet (mur, autre robot)
pas de parametre
renvoie 1 char (8bits) pour connaitre quel zone est en contact (bit0 pour zone 1 ... bit7 pour zone 8*/
char get_status();

//TODO
close_connexion();

/*permet de connaitre le niveau de vie d'un robot
- pas de parametre
- renvoie un entier qui représente le % de vie du robot (0-100)*/
int getlife();

/*permet au robot de scanner grossierement à 360° les obstacles sur 8 zones et renvoie la distance la plus courte pour chaque zone
- pas de parametre
- renvoie un pointeur vers tableau de 8 floats (1 par zone) correspondant à la distance la plus courte*/
scanlight scan_light();

/*permet au robot de scanner finement les obstacles sur une zone de 30° (12 zones) et renvoie les 10 objets les plus proches
prend en parametre:
    - le numero de zone à scanner (1 - 12)
renvoie un pointeur vers la structure scanfin (10 objets les plus proches et leurs types)
0 = pas d'objet
1 = mur
2 = robot ennemi
3 = missile
*/
scanfin scan_fin(int zone);

/*permet au robot de tirer un missile dans une direction donnée
prend en parametre:
    - l'angle de tir en radian (float)
    - ne renvoie rien*/
void missile_shoot(float teta):

/*permet de connaitre le nombre de missiles tirés non explosés
pas de parametre
renvoie :
    - un entier qui correspond aux nombres de missiles tirés*/
int missile_status();

//optionnel : renvoyer le nb de robot encore vivant (à faire plus tard)


#endif // ROBOT_API_H
