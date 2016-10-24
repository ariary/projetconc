/*
 *
 * File: mythreads.cpp
 * Author: Adrien Prestini & Antoine Rabenandrasana
 * 
 * Version: rendu du 10 octobre 2016
 */

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
bool isOnNE(personne p){
  return p.get_pos_y() >= 255 && p.get_pos_x() <=63;
}
bool isOnNO(personne p){;
  return p.get_pos_y() < 256 && p.get_pos_x() < 64;
}
bool isOnSE(personne p){
  return p.get_pos_y() >= 255 && p.get_pos_x() > 63;
}
bool isOnSO(personne p){
  return p.get_pos_y() < 256 && p.get_pos_x() > 63;
}

void *thread_avancerNE(void *p_data){ //peut être iterateur pour parcourir les joueurs de la zone

  cout<<"NE"<<endl;
	if (p_data != NULL)
  {
     	terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
      //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Est
      while (!t->finish()){
        for(int i = 0; i < t->liste_personnes.size(); i++){
          if(isOnNE(t->liste_personnes.at(i)))
            t->avancer(t->liste_personnes.at(i));
        }
      }

  }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNE())"<<endl;
  }

}

void *thread_avancerNO(void *p_data){
  cout<<"NO"<<endl;
    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
      //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Ouest
       while (!t->finish()){
        for(int i = 0; i < t->liste_personnes.size(); i++){
          if(isOnNO(t->liste_personnes.at(i)))
            t->avancer(t->liste_personnes.at(i));
        }
      }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: avancerNO())"<<endl;
   }
}

void *thread_avancerSE(void *p_data){
  cout<<"SE"<<endl;
    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif
        //on va s'occuper uniquement des personnes qui sont dans la zone Sud-Est
        while (!t->finish()){
        for(int i = 0; i < t->liste_personnes.size(); i++){
          if(isOnSE(t->liste_personnes.at(i)))
            t->avancer(t->liste_personnes.at(i));
        }
      }

   }else{
      cout<< "problème dans la récupération du contexte applicatif du thread (-t1: (avancerSE())"<<endl;
   }
}

void *thread_avancerSO(void *p_data){
  cout<<"SO"<<endl;
    if (p_data != NULL)
   {
      
        terrain* t=(terrain*) p_data;// recuperation du contexte applicatif 
        //on va s'occuper uniquement des personnes qui sont dans la zone Sud-Ouest
        while (!t->finish()){
        for(int i = 0; i < t->liste_personnes.size(); i++){
          if(isOnSO(t->liste_personnes.at(i)))
            t->avancer(t->liste_personnes.at(i));
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