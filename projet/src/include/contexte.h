/*
 * contexte.h
 *
 *  Created on: 24 oct. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 *
 *
 * Declaration de la classe Contexte: contenant les données livrées aux diffé-
 * rents threads. Elle a pour but de différencier les différentes étapes du pro-
 * jet. Par exemple pour l'étape 1 le pointeur sur la sémaphore est null.(nullptr)
 */

 #ifndef CONTEXTE_H_
#define CONTEXT_H_

#include "terrain.h"
#include <semaphore.h>

class terrain {

public:
	terrain* t; //pointeur sur terrain car : pas le terrain n'a pas le même cycle de vie que le contexte et je ne veux pas une copie
	sem_t *mutex;
	
}