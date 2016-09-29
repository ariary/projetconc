#include "include/mythreads.h"
#include <iostream>

using namespace std;
using namespace terrain;

/*t0*/
void *thread_avancerALL (void *p_data){
	cout<<"avancerALL()"<<endl;
	if (p_data != NULL)
   {
      /* recuperation du contexte applicatif */
      terrain *ter= p_data;
      while(!finish()){
      	
      }
   }else{
   	cout< "problème dans la récupération du contexte applicatif du thread (-t0)"
   }
} 

/*t1*/
void *thread_avancerNE(void *pd_data){
	cout<<"avancerNE()"<<endl;
}

void *thread_avancerNO(void *pd_data){
	cout<<"avancerNO()"<<endl;
}

void *thread_avancerSE(void *pd_data){
	cout<<"avancerSE()"<<endl;
}

void *thread_avancerSO(void *pd_data){
	cout<<"avancerSO()"<<endl;
}

/*t2*/
void *thread_avancerALONE(void *pd_data){
	cout<<"avancerALONE()"<<endl;
}