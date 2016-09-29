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
void *thread_avancerNE(void *pd_data){ //peut être iterateur pour parcourir les joueurs de la zone
	cout<<"avancerNE()"<<endl;
	if (p_data != NULL)
   {
    	
      	terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
   }else{
   		cout<< "problème dans la récupération du contexte applicatif du thread (-t1)"<<endl;
   }
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