// robot_api.h version 0.3 du 07/12/15 
/* liste des fonctions pour le simulateur*/ 
 

#ifndef ROBOT_API_H 
#define ROBOT_API_H 
 
 
#include <stdio.h> 

#define CLEF 12345 // je définis une clef au hasard

//	Je définis une structure de memoire partagee.
typedef struct
{
	char *tab_cmd[10];
	int flag_w[10];
	int flag_r[10];
}structure_partagee;
 
 
//definition des structures 
typedef struct { 
 	float x;	//position x en metre du centre du robot 
 	float y;	//position y en metre du cnetre du robot 
 	float teta;	//angle en radian (entre 0 et 2pi)
	
/******uniqument pour la simu choix a faire *********************/
	float speed; //vitesse du robot
	int id_player; //identifiant du robot connecté
	int life_point;	//Vie restante en pourcent 
	int nb_missile;	//Nb de missiles tirés
	int existe; //0 = pas de robot; 1 = robot présent

 }s_robot; 
 
 
 typedef struct { 
     float x;    //position x en metre en tête du missile 
     float y;    //position y en metre en tête du missile 
     float teta; //angle relatif du missile pas rapport à l'axe x en radian
     int existe; //0 = pas de missile; 1 = missile présent

/******uniqument pour la simu   choix a faire *********************/
	int id_shooter; //permet de savoir qui tue qui

 }s_missile; 
 
 
 //definit les points de depart et de fin du mur Xdebut, Ydebut Xfin, Yfin  en float 
 //ainsi qu'un entier qui nous renseigne sur la présence du mur (0 = pas de mur; 1 = mur présent) 
 typedef struct { 
     float Xdebut; 
     float Ydebut; 
     float Xfin; 
     float Yfin; 
     int existe; 
 }s_mur; 
 
 
 typedef struct { 
 float zone_distance[8]; // tableau correspondant au scan light pour les 8 zones 
 }scanlight; 
 
 
 typedef struct { 
     float dist_scan[10]; // les 10 distances les plus courtes pour le scan selectionnée 
     int type_scan[10]; //type d'objet scanné sur la zone scannée 
 }scanfin; 
 
 
 

 /*Initialisation des connexions TCP/IP 
46 prend en paramètre : 
47 	- un nom de robot 
48 	- l'adresse ip du serveur pour la connexion 
49 	- le port pour la connexion 
50 renvoie id du joueur, renvoie -1 si problème de connexion, code d'erreur à préciser par la suite*/ 
 int init_connexion(char *nom, char *ip); 
 
 
 /*permet de récupérer la position d'un robot: 
54 pas de parametre 
55 renvoie une structure s_robot*/ 
s_robot* get_position(int id); 
 
 
 /*permet de demander de déplacer un robot 
59 prend en parametre : 
60     - la vitesse du robot (speed) en m/s 
61     - la direction du robot en radian 
62 ne renvoie rien*/ 
 void move(float speed, float teta); 
 
 
 /*permet de connaitre l'etat du robot, pour savoir si il touche un objet (mur, autre robot) 
66 pas de parametre 
67 renvoie 1 char (8bits) pour connaitre quel zone est en contact (bit0 pour zone 1 ... bit7 pour zone 8*/ 
 char get_status(int id); 
 
 
 //TODO 
 void close_connexion(); 
 
 
 /*permet de connaitre le niveau de vie d'un robot 
74 - pas de parametre 
75 - renvoie un entier qui représente le % de vie du robot (0-100)*/ 
 int getlife(); 
 
 
 /*permet au robot de scanner grossierement à 360° les obstacles sur 8 zones et renvoie la distance la plus courte pour chaque zone 
79 - pas de parametre 
80 - renvoie un pointeur vers tableau de 8 floats (1 par zone) correspondant à la distance la plus courte*/ 
 scanlight* scan_light(); 
 
 
 /*permet au robot de scanner finement les obstacles sur une zone de 30° (12 zones) et renvoie les 10 objets les plus proches 
84 prend en parametre: 
85     - le numero de zone à scanner (1 - 12) 
86 renvoie un pointeur vers la structure scanfin (10 objets les plus proches et leurs types) 
87 0 = pas d'objet 
88 1 = mur 
89 2 = robot ennemi 
90 3 = missile 
91 */ 
 scanfin* scan_fin(int zone); 
 
 
 /*permet au robot de tirer un missile dans une direction donnée 
95 prend en parametre: 
96     - l'angle de tir en radian (float) 
97     - ne renvoie rien*/ 
 void missile_shoot(float teta); 
 
 
 /*permet de connaitre le nombre de missiles tirés non explosés 
101 pas de parametre 
102 renvoie : 
103     - un entier qui correspond aux nombres de missiles tirés*/ 
 int missile_status(); 
 

 //optionnel : renvoyer le nb de robot encore vivant (à faire plus tard) 
 
 
 
 
 #endif // ROBOT_API_H 
