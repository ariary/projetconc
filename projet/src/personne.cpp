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
	this->print_personne();
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