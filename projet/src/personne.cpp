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

}

void personne::set_position(int x, int y){
	this->position_x = x;
	this->position_y = y;
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

void personne::changer_position(int newX, int newY){
	this->position_x = newX;
	this->position_y = newY;

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

bool personne::near_NO(){
	//je suis en zone NE
	if(!(au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_y-1 == 255;
	//je suis en zone SO
	if((au_dessous_azimuth2()) && !(droite_du_centre()))
		return this->position_x-1 == 63;


	//je suis en zone SE, on doit vérifier si on est au centre de la map (croisement des zones)
	if((au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_x-1 == 63 && this->position_y-1 == 255;
}

bool personne::near_SO(){
	//je suis en zone SE
	if((au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_y-1 == 255;
	//je suis en zone NO
	if(!(au_dessous_azimuth2()) && !(droite_du_centre()))
		return this->position_x+1 == 64;


	//je suis en zone NE
	if(!(au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_y-1 == 255 && this->position_x+1 == 64;
}

bool personne::near_SE(){
	//je suis en zone NE
	if(!(au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_x+1 == 64;
}

bool personne::near_NE(){
	//je suis en zone SE
	if((au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_x-1 == 63;
}


bool personne::isOut(){
	return position_x == -1 && position_y == -1;
}