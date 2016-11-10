/*
 *
 * File: mythreads.cpp
 * Author: Adrien Prestini & Antoine Rabenandrasana
 * 
 * Version: rendu du 10 octobre 2016
 * Modification: rendu du 7 novembre 2016
 */

#include "include/mythreads.h"
#include <iostream>
#include "include/contexte.h"

using namespace std;
/*t0*/

/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  sur le terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerALL (void *p_data){
	cout<<"avancerALL()"<<endl;
	if (p_data != nullptr)
   {
    	
      	Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;


    	  while(!t->finish()){
      		for(int i=0;i<t->liste_personnes.size();i++)
      			t->avancer(t->liste_personnes.at(i));
      }
   }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t0): sortie du programme"<<endl;
    exit(1);
   }
} 




/*t1*/

/*
 * Les quatres fonctions suivantes permettent de faire avancer
 * toutes les personnes présentes dans une certaine zone.
 * zones possibles: NO, SO, NE, SE
 */
static void avancer_all_NO(terrain *t);
static void avancer_all_SO(terrain *t);
static void avancer_all_NE(terrain *t);
static void avancer_all_SE(terrain *t);


/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  dans la zone NE du terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerNE(void *p_data){ //peut être iterateur pour parcourir les joueurs de la zone

  if (p_data != nullptr)
   {
      
      Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
      terrain* t=c->t;

      //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Est
      switch (c->_etape)
      {
        case 1: /*Etape 1*/
            while (!t->finish()){
              avancer_all_NE(t);
            }
            break;

        case 2: /*Etape 2*/
            sem_t* mutex=c->mutex;
            while(1){

              if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
              {
                  perror("sem_wait() in mythread.cpp");
                  exit(1);
              } 

              if (t->finish()){
                if(sem_post(mutex)==-1) //je libère la sémaphore avant de quitter le thread
                {
                    perror("sem_post()");
                    exit(1);
                }
                break;
              }

              avancer_all_NE(t);

              if(sem_post(mutex)==-1) //je libère le terraind
              {
                  perror("sem_post()");
                  exit(1);
              }
            }

            /*je fais down sur la sémaphore du thread avant d'en sortir*/
            if (c->join != nullptr){
              if(sem_post(c->join)==-1)
              {
                  perror("sem_post()");
                  exit(1);
              }
            }else{
              cerr<<"Semaphore de threads inéxistantes (nullptr): sortie du programme"<<endl;
              exit(1);
            }           
            break;
    }

  }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t1): sortie du programme"<<endl;
    exit(1);
  }

}


/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  dans la zone NO du terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerNO(void *p_data){
  
  if (p_data != nullptr)
   {
      
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;
      //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Ouest
      switch(c->_etape){
        case 1:

          while (!t->finish()){
            avancer_all_NO(t);
          }

          break;

        case 2:
            sem_t* mutex=c->mutex;
            while(1){

              if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
              {
                  perror("sem_wait() in mythread.cpp");
                  exit(1);
              }
              if (t->finish()){
                if(sem_post(mutex)==-1) //je libère la sémaphore avant de quitter le thread
                {
                    perror("sem_post()");
                    exit(1);
                }
                break;
              }

              avancer_all_NO(t);

              if(sem_post(mutex)==-1) //je libère le terrain
              {
                  perror("sem_post()");
                  exit(1);
              }
            }

            /*je fais down sur la sémaphore du thread avant d'en sortir*/
            if (c->join != nullptr){
              if(sem_post(c->join)==-1) //je libère la sémaphore avant de quitter le thread
              {
                  perror("sem_post()");
                  exit(1);
              }
            }else{
              cerr<<"Semaphore de threads inéxistantes (nullptr): sortie du programme"<<endl;
              exit(1);
            }
            break;
      }

   }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t1): sortie du programme"<<endl;
    exit(1);
   }
}


/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  dans la zone SE du terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerSE(void *p_data){
  if (p_data != nullptr)
   {
      
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;
        //on va s'occuper uniquement des personnes qui sont dans la zone Sud-Est

        switch(c->_etape){
          case 1:

              while (!t->finish()){
                avancer_all_SE(t);
              }
              break; 

          case 2:
            sem_t* mutex=c->mutex;
            while(1){

              if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
              {
                  perror("sem_wait() in mythread.cpp");
                  exit(1);
              }
              
              if (t->finish()){
                if(sem_post(mutex)==-1) //je libère la sémaphore avant de quitter le thread
                {
                    perror("sem_post()");
                    exit(1);
                }
                break;
              }

              avancer_all_SE(t);

              if(sem_post(mutex)==-1) //je libère le terrain
              {
                  perror("sem_post()");
                  exit(1);
              }
            }

            /*je fais down sur la sémaphore du thread avant d'en sortir*/
            if (c->join != nullptr)
            {
              if(sem_post(c->join)==-1) //je libère la sémaphore avant de quitter le thread
              {
                  perror("sem_post()");
                  exit(1);
              }
            }else{
              cerr<<"Semaphore de threads inéxistantes (nullptr): sortie du programme"<<endl;
              exit(1);
            }            
            break;
        }

   }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t1): sortie du programme"<<endl;
    exit(1);
   }
}

/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  dans la zone SO du terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerSO(void *p_data){
 
  if (p_data != nullptr)
   {
      
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;
        //on va s'occuper uniquement des personnes qui sont dans la zone Sud-Ouest

        switch(c->_etape){
          case 1:
              while (!t->finish()){
                avancer_all_SO(t);
              }
              break;
          case 2:
            sem_t* mutex=c->mutex;
            while(1){

              if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
              {
                  perror("sem_wait() in mythread.cpp");
                  exit(1);
              }

              if (t->finish()){
                if(sem_post(mutex)==-1) //je libère la sémaphore avant de quitter le thread
                {
                    perror("sem_post()");
                    exit(1);
                }
                break;
              }

              avancer_all_SO(t);

              if(sem_post(mutex)==-1) //je libère le terrain
              {
                  perror("sem_post()");
                  exit(1);
              }
            }

            /*je fais down sur la sémaphore du thread avant d'en sortir*/
            if (c->join != nullptr)
            {
                if(sem_post(c->join)==-1) //je libère la sémaphore avant de quitter le thread
                {
                    perror("sem_post()");
                    exit(1);
                }
            }else{
              cerr<<"Semaphore de threads inéxistantes (nullptr): sortie du programme"<<endl;
              exit(1);
            }            
            break;

        }

   }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t1): sortie du programme"<<endl;
    exit(1);
   }
}

/*t2*/


/**
 *  Thread qui fait avancer une seule personne sur le 
 *  terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerALONE(void *p_data){
  if (p_data != nullptr)
   {
      cout<<"debut thread"<<endl;
      
      Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
      terrain my_terrain=*(c->t);
      personne my_personne=*(c->_pers);
      cout<<"before switch "<<(c->_etape)<<endl;
      if (c->join != nullptr)c->_etape=2;
      switch(c->_etape){
        case 1:
            cout<<"case 1"<<endl;
            while(!my_personne.aFini())
              my_terrain.avancer(my_personne);
            break;
        case 2:
            cout<<"case 2"<<endl;
            sem_t* mutex=c->mutex;
            while(!my_personne.aFini())
            {
              if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
              {
                perror("sem_wait() in mythread.cpp");
                exit(1);
              }
              my_terrain.avancer(my_personne);
              if(sem_post(mutex)==-1)
              {
                  perror("sem_post()");
                  exit(1);
              }
            }

            /*je fais down sur la sémaphore privée du thread avant d'en sortir*/
            if (c->join != nullptr){
               if(sem_post(c->join)==-1) //je libère la sémaphore avant de quitter le thread
               {
                   perror("sem_post()");
                   exit(1);
               }
            }
            else{
              cerr<<"Semaphore de threads inéxistantes (nullptr): sortie du programme"<<endl;
              exit(1);
            }    
            cout<<"fin thread"<<endl;
            break;            
      }


  }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t2): sortie du programme"<<endl;
    exit(1);
  }
}

/*definition des fonctions*/

/*
 * Permet de determiner si une personne est dans la zone NE
 */
bool isOnNE(personne p){
  return p.get_pos_y() >= 255 && p.get_pos_x() <=63;
}

/*
 * Permet de determiner si une personne est dans la zone NO
 */
bool isOnNO(personne p){;
  return p.get_pos_y() < 256 && p.get_pos_x() < 64;
}

/*
 * Permet de determiner si une personne est dans la zone SE
 */
bool isOnSE(personne p){
  return p.get_pos_y() >= 255 && p.get_pos_x() > 63;
}

/*
 * Permet de determiner si une personne est dans la zone SO
 */
bool isOnSO(personne p){
  return p.get_pos_y() < 256 && p.get_pos_x() > 63;
}


/*
 * Fait avancer toutes les personnes présentes dans la zone SO
 */
static void avancer_all_SO(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnSO(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone SE
 */
static void avancer_all_SE(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnSE(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone NE
 */
static void avancer_all_NE(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnNE(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone NO
 */
static void avancer_all_NO(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnNO(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}