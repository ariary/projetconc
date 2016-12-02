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
Contexte::Contexte(int num_etap,terrain* ter,map<string,sem_t*> *map_sem,personne* pers,sem_t* mutex){
	this->_etape=num_etap;
	this->t=ter;
	this->map_sem=map_sem;
	this->_pers=pers;
	this->mutex=mutex;
}



/*
 *  Seteur:
 *	- Moniteur
 *	-Join (mutex privée)
 *	-CyclicBarrier
 */

void Contexte::setMoniteur(Moniteur* m){
	this->m=m;
}


void Contexte::setCyclicBarrier(CyclicBarrier* barrier){
	this->barrier=barrier;
}

void Contexte::setSemaphore(sem_t* mutex){
	this->mutex=mutex;
}

void Contexte::setPersonne(personne* p){
	this->_pers=p;
}