/*
 * contexte.cpp
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 */
 #include "include/contexte.h"


Contexte::Contexte(terrain* ter,sem_t* mut){
	this->t=ter;
	this->mutex=mut;
}