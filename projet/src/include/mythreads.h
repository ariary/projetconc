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
void *thread_avancerZone1(void *pd_data);
void *thread_avancerZone2(void *pd_data);
void *thread_avancerZone3(void *pd_data);
void *thread_avancerZone4(void *pd_data);

/*
 * fonctions suivantes permettent de faire avancer
 * toutes les personnes présentes dans une certaine zone.
 * zones possibles: NO, SO, NE, SE
 */

//-----------------------------
//			etape 1
//-----------------------------
 void avancer_all_Zone1(terrain *t);
 void avancer_all_Zone2(terrain *t);
 void avancer_all_Zone3(terrain *t);
 void avancer_all_Zone4(terrain *t);
//-----------------------------
//			etape 2
//-----------------------------
void avancer_Zone1_moniteur(terrain* t,personne* p);
void avancer_Zone2_moniteur(terrain* t,personne* p);
void avancer_Zone3_moniteur(terrain* t,personne* p);
void avancer_Zone4_moniteur(terrain* t,personne* p);


//outils pour connaitre la région d'une personne
bool isOnZone1(personne p);
bool isOnZone2(personne p);
bool isOnZone3(personne p);
bool isOnZone4(personne p);

/*t2*/
void *thread_avancerALONE(void *pd_data);



#endif
