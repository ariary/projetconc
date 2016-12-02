/*
 * mythreads.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#ifndef MYTHREADS_H_
#define MYTHREADS_H_


#include "personne.h"
#include "terrain.h"
#include <semaphore.h>

/*t0*/
void *thread_avancerALL (void *p_data); 

/*t1*/
void *thread_avancerNE(void *pd_data);
void *thread_avancerNO(void *pd_data);
void *thread_avancerSE(void *pd_data);
void *thread_avancerSO(void *pd_data);

/*
 * fonctions suivantes permettent de faire avancer
 * toutes les personnes présentes dans une certaine zone.
 * zones possibles: NO, SO, NE, SE
 */

//-----------------------------
//			etape 1
//-----------------------------
 void avancer_all_NO(terrain *t);
 void avancer_all_SO(terrain *t);
 void avancer_all_NE(terrain *t);
 void avancer_all_SE(terrain *t);
//-----------------------------
//			etape 2
//-----------------------------
void avancer_NO_moniteur(terrain* t,personne* p);
void avancer_SO_moniteur(terrain* t,personne* p);
void avancer_NE_moniteur(terrain* t,personne* p);
void avancer_all_SE(terrain* t,personne* p);


//outils pour connaitre la région d'une personne
bool isOnNE(personne p);
bool isOnNO(personne p);
bool isOnSE(personne p);
bool isOnSO(personne p);

/*t2*/
void *thread_avancerALONE(void *pd_data);



#endif
