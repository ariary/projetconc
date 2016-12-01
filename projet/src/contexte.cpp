/*
 * contexte.cpp
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *	Version: rendu du 7 novembre 2016
 */
 #include "include/contexte.h"

//-----------------------------
//			CONTEXTE
//-----------------------------
Contexte::Contexte(int num_etap,terrain* ter,map<string,sem_t*> *map_sem,sem_t* join,personne* pers,sem_t* mutex){
	this->_etape=num_etap;
	this->t=ter;
	this->map_sem=map_sem;
	this->_pers=pers;
	this->join=join;
	this->mutex=mutex;
}

void Contexte::setMoniteur(Moniteur* m){
	this->m=m;
}

void Contexte::setJoin(sem_t *join){
	this->join=join;
}


//-----------------------------
//			MONITEUR
//-----------------------------

Moniteur::Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex){
	this->cond=cond;
	this->mutex=mutex;
}