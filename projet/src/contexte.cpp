/*
 * contexte.cpp
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *	Version: rendu du 7 novembre 2016
 */
 #include "include/contexte.h"


Contexte::Contexte(int num_etap,terrain* ter,map<string,sem_t*> *map_sem,sem_t* join,personne* pers,sem_t* mutex){
	this->_etape=num_etap;
	this->t=ter;
	this->map_sem=map_sem;
	this->_pers=pers;
	this->join=join;
	this->mutex=mutex;
}