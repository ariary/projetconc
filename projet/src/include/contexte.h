/*
 * contexte.h
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *	Version: rendu du 7 novembre 2016
 *
 * Declaration de la classe Contexte: contenant les données livrées aux diffé-
 * rents threads.
 * Cette classe est plus utilisée comme une structure.
 */

 #ifndef CONTEXTE_H_
#define CONTEXT_H_

#include <cstddef>
#include "terrain.h"
#include <semaphore.h>
#include <map>
#include <string>
 #include "CyclicBarrier.h"
using namespace std;

class Moniteur
{
	public:
		pthread_cond_t* cond; //tableau de condition
		pthread_mutex_t mutex;

		Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex);
};

class Contexte {

	public:
		int _etape; //utilisé dans mythread.cpp
		terrain* t; //pointeur sur terrain car : pas le terrain n'a pas le même cycle de vie que le contexte et je ne veux pas une copie
		map<string,sem_t*> *map_sem; //map avec un mutex pour chaque zone
		sem_t *join; //etape2
		sem_t *mutex;
		personne *_pers;
		Moniteur* m;
		CyclicBarrier* barrier;


		Contexte(int num_etap,terrain* ter,map<string,sem_t*> *map_sem=nullptr,sem_t* join=nullptr,personne* pers=nullptr,sem_t* mutex=nullptr);

		void setMoniteur(Moniteur* m);
		void setJoin(sem_t *join);
		void setCyclicBarrier(CyclicBarrier* barrier);
		void setSemaphore(sem_t* mutex);
		void setPersonne(personne* p);

};

#endif