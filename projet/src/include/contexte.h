/*
 * contexte.h
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *	Version: rendu du 7 novembre 2016
 *
 * Declaration de la classe Contexte: contenant les données livrées aux diffé-
 * rents threads. Elle a pour but de différencier les différentes étapes du pro-
 * jet. Par exemple pour l'étape 1 le pointeur sur la sémaphore est null.(nullptr)
 */

 #ifndef CONTEXTE_H_
#define CONTEXT_H_

#include <cstddef>
#include "terrain.h"
#include <semaphore.h>
#include <map>
#include <string>

using namespace std;

class Contexte {

public:
	int _etape; //utilisé dans mythread.cpp
	terrain* t; //pointeur sur terrain car : pas le terrain n'a pas le même cycle de vie que le contexte et je ne veux pas une copie
	map<string,sem_t*> *map_sem; //map avec un mutex pour chaque zone
	sem_t *join;
	personne *_pers;

	Contexte(int num_etap,terrain* ter,map<string,sem_t*> *map_sem=nullptr,sem_t* join=nullptr,personne* pers=nullptr);
};

#endif