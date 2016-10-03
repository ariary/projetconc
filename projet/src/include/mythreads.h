/*
 * thread.h
 *
 *  Created on: 24 sept. 2016
 *      Author: Adrien Prestini & Antoine Rabenandrasana
 */

#ifndef MYTHREADS_H_
#define MYTHREADS_H_


#include "personne.h"
#include "terrain.h"

/*t0*/
void *thread_avancerALL (void *p_data); 

/*t1*/
void *thread_avancerNE(void *pd_data);
void *thread_avancerNO(void *pd_data);
void *thread_avancerSE(void *pd_data);
void *thread_avancerSO(void *pd_data);

/*t2*/
void *thread_avancerALONE(void *pd_data);

typedef struct Data Data;
struct Data
{
   terrain t;
   int indice_personne;
};

#endif
