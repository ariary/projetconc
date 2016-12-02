#include "./include/Moniteur.h"

//-----------------------------
//			MONITEUR
//-----------------------------

Moniteur::Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex){
	this->cond=cond;
	this->mutex=mutex;

	
	this->NEavailable=1;
	this->SEavailable=1;
	this->SOavailable=1;
	this->NOavailable=1;
}