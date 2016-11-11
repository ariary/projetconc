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
	if(!(au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_y-1 == 255;
}

bool personne::near_SO(){
	if((au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_y-1 == 255;
}

bool personne::near_SE(){
	if(!(au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_x+1 == 64;
}

bool personne::near_NE(){
	if((au_dessous_azimuth2()) && (droite_du_centre()))
		return this->position_x-1 == 63;
}

//les frontieres verticales (d'où le (2) dans la fonction)
bool personne::near_SO2(){
	if(!(au_dessous_azimuth2()) && !(droite_du_centre()))
		return this->position_x+1 == 64;
}

//les frontieres verticales (d'où le (2) dans la fonction)
bool personne::near_NO2(){
	if((au_dessous_azimuth2()) && !(droite_du_centre()))
		return this->position_x-1 == 63;
}