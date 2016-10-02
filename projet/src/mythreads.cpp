#include "include/mythreads.h"
#include <iostream>

using namespace std;

/*t0*/
void *thread_avancerALL (void *p_data){
	cout<<"avancerALL()"<<endl;
	if (p_data != NULL)
   {
    	
      	terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 

    	while(!t->finish()){
      		for(int i=0;i<t->liste_personnes.size();i++){
      			//t->liste_personnes[i].avancer();
      			t->print_liste_personnes();
      		}
      	}
   }else{
   		cout<< "problème dans la récupération du contexte applicatif du thread (-t0)"<<endl;
   }
} 

/*t1*/
void *thread_avancerNE(void *p_data){ //peut être iterateur pour parcourir les joueurs de la zone

	if (p_data != NULL)
   {
    	
      	terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
   }else{
   		cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNE())"<<endl;
   }
}

void *thread_avancerNO(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNO())"<<endl;
   }

   
}

void *thread_avancerSE(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: (avancerSE())"<<endl;
   }
}

void *thread_avancerSO(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1)"<<endl;
   }
}

/*t2*/
void *thread_avancerALONE(void *pd_data){
	cout<<"avancerALONE()"<<endl;
}