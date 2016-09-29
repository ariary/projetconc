#include "include/mythreads.h"
#include <iostream>

using namespace std;
using namespace terrain;

/*t0*/
void *thread_avancerALL (void *p_data){
	cout<<"avancerALL()"<<endl;
	if (p_data != NULL)
   {
    	
      	terrain *ter= p_data;// recuperation du contexte applicatif 

    	while(!finish()){
      		for(int i=0;i<ter.liste_personnes.size();i++){
      			ter.liste_personnes[i].avancer();
      		}
      	}
   }else{
   		cout<< "problème dans la récupération du contexte applicatif du thread (-t0)"<<endl;
   }
} 

/*t1*/
void *thread_avancerNE(void *pd_data){ //peut être iterateur pour parcourir les joueurs de la zone
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