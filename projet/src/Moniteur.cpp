#include "./include/Moniteur.h"
#include <iostream>
#include <cstdio>
using namespace std;

//-----------------------------
//			MONITEUR
//-----------------------------

Moniteur::Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex){
	this->cond=cond;
	this->mutex=mutex;
	
	this->available=1;
}

Moniteur::Moniteur(){

	//zone1
	pthread_mutex_t lock1;
	if (pthread_mutex_init(&lock1, NULL) != 0)
	{
	    cout<<">> (Moniteur) initialisation du mutex échouée"<<endl;
	    exit(1);
	}
	pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
	pr_zone1=make_pair(lock1,cond1);

	//zone2
	pthread_mutex_t lock2;
	if (pthread_mutex_init(&lock2, NULL) != 0)
	{
	    cout<<">> (Moniteur) initialisation du mutex échouée"<<endl;
	    exit(1);
	}
	pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
	pr_zone2=make_pair(lock2,cond2);

	//zone3
	pthread_mutex_t lock3;
	if (pthread_mutex_init(&lock3, NULL) != 0)
	{
	    cout<<">> (Moniteur) initialisation du mutex échouée"<<endl;
	    exit(1);
	}
	pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
	pr_zone3=make_pair(lock3,cond3);

	//zone4
	pthread_mutex_t lock4;
	if (pthread_mutex_init(&lock4, NULL) != 0)
	{
	    cout<<">> (Moniteur) initialisation du mutex échouée"<<endl;
	    exit(1);
	}
	pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;
	pr_zone4=make_pair(lock4,cond4);
}