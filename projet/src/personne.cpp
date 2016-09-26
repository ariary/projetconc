/*
 * Personne.cpp
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#include "include/personne.h"

personne::personne(int x, int y){
	this->position_x = x;
	this->position_y = y;

}
void personne::avancer_nord_ouest(){}
void personne::avancer_nord(){}
void personne::avancer_nord_est(){}
void personne::avancer_est(){}
void personne::avancer_sud_est(){}
void personne::avancer_sud(){}
void personne::avancer_sud_ouest(){}
void personne::avancer_ouest(){}

int personne::get_pos_x(){
	return this->position_x;
}
int personne::get_pos_y(){
	return this->position_y;
}

