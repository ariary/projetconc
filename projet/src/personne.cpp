/*
 * File: Personne.cpp
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 * Version: rendu du 10 octobre 2016
 */

#include "include/personne.h"


personne::personne(int x, int y){
	this->position_x = x;
	this->position_y = y;
	majZone();

}
void personne::majZone(){
	if(position_y >= 0 && position_y <= 127)
		numZoneActuelle = 1;
	if(position_y >=128 && position_y <= 255)
		numZoneActuelle = 2;
	if(position_y >=256 && position_y <= 383)
		numZoneActuelle = 3;
	if(position_y >=384 && position_y <= 512)
		numZoneActuelle = 4;
	if(position_y == -1)
		numZoneActuelle = 0;
}

void personne::set_position(int x, int y){
	this->position_x = x;
	this->position_y = y;
	majZone();
}
bool personne::aFini(){
	return this->position_x >= 60  && this->position_x <= 67 && this->position_y == 0;
}

int personne::get_pos_x(){
	return this->position_x;
}
int personne::get_pos_y(){
	return this->position_y;
}
int personne::getZone(){return numZoneActuelle;}

void personne::changer_position(int newX, int newY){
	this->position_x = newX;
	this->position_y = newY;
	std::cout << "salut fonction inutile" << std::endl;

}

/*
 * cette fonction affiche les coordonnées d'une personne
 * utilisée pour debbuger
 */
void personne::print_personne(){
	std::cout << "(" << this->position_x << ", " << this->position_y << ")" << std::endl;
}

bool personne::au_dessus_azimuth1(){
	return this->position_x < 60;
}

bool personne::au_dessous_azimuth2(){
	return this->position_x > 63;
}

bool personne::droite_du_centre(){
	return this->position_y > 255;
}

bool personne::isOut(){
	return position_x == -1 && position_y == -1;
}


bool personne::near_Zone1(){
	return position_y-1 == 127;
}

bool personne::near_Zone2(){
	return position_y-1 == 255;
}

bool personne::near_Zone3(){
	return position_y-1 == 383;
}



