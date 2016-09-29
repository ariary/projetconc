/*
 * Personne.cpp
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#include "include/personne.h"
#include <iostream>


personne::personne(int x, int y){
	this->position_x = x;
	this->position_y = y;
	this->position_x_fin = position_x + 3;
	this->position_y_fin = position_y + 3;

}
bool personne::aFini(){
	return (this->position_x > 60  && this->position_x < 68) && this->position_y == 0;
}
/*void personne::avancer_nord_ouest(){
	this->position_x--;
	this->position_y--; 
}
void personne::avancer_nord(){
	this->position_x--;
}
void personne::avancer_nord_est(){
	this->position_x--;
	this->position_y++;
}
void personne::avancer_est(){
	this->position_y++;
}
void personne::avancer_sud_est(){
	this->position_x++;
	this->position_y++;
}
void personne::avancer_sud(){
	this->position_x++;
}
void personne::avancer_sud_ouest(){
	this->position_x++;
	this->position_y--;
}
void personne::avancer_ouest(){
	this->position_y--;
}*/

int personne::get_pos_x(){
	return this->position_x;
}
int personne::get_pos_y(){
	return this->position_y;
}
int personne::get_pos_x_fin(){
	return this->position_x_fin;
}
int personne::get_pos_y_fin(){
	return this->position_y_fin;
}
void personne::print_personne(){
	std::cout << "(" << this->position_x << ", " << this->position_y << ")" << std::endl;
}
