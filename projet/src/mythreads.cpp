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
      		for(int i=0;i<t->liste_personnes.size();i++)
      			//t->avancer_personne(i);
            cout << "coucou" << endl;
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

      while (  (!(t->get_vector_personneNE().empty()) || !(t->get_vector_personneSE().empty())) ){
        if (!t->get_vector_personneNE().empty())
        {
          for(int i=0;i<t->get_vector_personneNE().size();i++)
            t->avancer(t->get_vector_personneNE()[i]);
        }
      }

  }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNE())"<<endl;
  }

}

void *thread_avancerNO(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 

        while (  !(t->finish()) ){
          
          if ( !(t->get_vector_personneNO().empty()) )
          {
            for(int i=0;i<t->get_vector_personneNO().size();i++)
              t->avancer(t->get_vector_personneNO()[i]);      
          }

        }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNO())"<<endl;
   }
}

void *thread_avancerSE(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif


        while (  (!(t->get_vector_personneSE().empty()) || !(t->get_vector_personneNE().empty())) ){
          if (!t->get_vector_personneSE().empty())
          {
            for(int i=0;i<t->get_vector_personneSE().size();i++)
              t->avancer(t->get_vector_personneSE()[i]);
          }
        }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: (avancerSE())"<<endl;
   }
}

void *thread_avancerSO(void *p_data){

    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 

        while (  !(t->finish()) ){
          
          if ( !(t->get_vector_personneSO().empty()) )
          {
            for(int i=0;i<t->get_vector_personneSO().size();i++)
              t->avancer(t->get_vector_personneSO()[i]);
          }

        }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1)"<<endl;
   }
}

/*t2*/
/*void *thread_avancerALONE(void *p_data){
	if (p_data != NULL)
  {
    Data* p = p_data;
    my_terrain=p->t;
    my_personne=my_terrain.liste_personnes[i];
    while(!my_personne.aFini())
      my_terrain.avancer(my_personne);

  }else{
    cout<< "problème dans la récupération du contexte applicatif du thread (-t2)"<<endl;
  }
}*/