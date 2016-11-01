/*
 * contexte.cpp
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *	Version: rendu du 7 novembre 2016
 */
 #include "include/contexte.h"


Contexte::Contexte(int num_etap,terrain* ter,sem_t* mut,sem_t* join,personne* pers){
	this->_etape=num_etap;
	this->t=ter;
	this->mutex=mut;
	this->_pers=pers;
	this->join=join;
}