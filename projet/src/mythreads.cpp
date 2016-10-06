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
      			t->avancer(t->liste_personnes.at(i));
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
      t->refresh_vector_personnesNE();
      t->refresh_vector_personnesSE();
      while (  (!(t->liste_personnesNE.empty()) || !(t->liste_personnesSE.empty()))){
        cout << t->liste_personnesNE.size() << endl;
        if (!t->liste_personnesNE.empty())
        {
          for(int i=0;i<t->liste_personnesNE.size();i++){
            t->avancer(t->liste_personnesNE.at(i));
          }
        }
        t->refresh_vector_personnesNE();
        t->refresh_vector_personnesSE();
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
          t->refresh_vector_personnesNO();
          if ( !(t->liste_personnesNO.empty()) )
          {
            for(int i=0;i<t->liste_personnesNO.size();i++)
              t->avancer(t->liste_personnesNO.at(i));      
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

        t->refresh_vector_personnesSE();
        t->refresh_vector_personnesNE();
        while (  (!(t->liste_personnesSE.empty()) || !(t->liste_personnesNE.empty())) ){
          if (!t->liste_personnesSE.empty())
          {
            for(int i=0;i<t->liste_personnesSE.size();i++)
              t->avancer(t->liste_personnesSE.at(i));
          }
          t->refresh_vector_personnesSE();
          t->refresh_vector_personnesNE();
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
          t->refresh_vector_personnesSO();
          if ( !(t->liste_personnesSO.empty()) )
          {
            for(int i=0;i<t->liste_personnesSO.size();i++)
              t->avancer(t->liste_personnesSO.at(i));
          }

        }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1)"<<endl;
   }
}

/*t2*/
void *thread_avancerALONE(void *p_data){
	if (p_data != NULL)
  {
    Data* p =(struct Data*) p_data;
    terrain my_terrain(p->terr);
    personne my_personne(p->pers);
    while(!my_personne.aFini())
      my_terrain.avancer(my_personne);

  }else{
    cout<< "problème dans la récupération du contexte applicatif du thread (-t2)"<<endl;
  }
}