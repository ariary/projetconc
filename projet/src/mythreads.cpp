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
#include <unistd.h>

using namespace std;
/*t0*/

/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  sur le terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerALL (void *p_data){
    cout<<">> lancement thread unique(-t0)"<<endl;
    if (p_data != nullptr)
   {
        
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;


          while(!t->finish()){
            for(int i=0;i<t->liste_personnes.size();i++){
                usleep(5000);
               //pour l'instant on ignore ceux qui sont deja arrivés
                if(t->liste_personnes.at(i).isOut())
                    continue;
                t->avancer(t->liste_personnes.at(i));
            }
      }
      cout<<">> fin thread unique(-t0)"<<endl;
   }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t0): sortie du programme"<<endl;
    exit(1);
   }
} 




/*t1*/


/**
 *  Thread qui fait avancer toutes les personnes présentes 
 *  dans la zone NE du terrain
 *
 *  @param Le contexte associé au thread
 */
void *thread_avancerZone1(void *p_data){ //peut être iterateur pour parcourir les joueurs de la zone
  cout<<">> lancement thread zone 1"<<endl;
  if (p_data != nullptr)
   {
      
      Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
      terrain* t=c->t;

      //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Est
      switch (c->_etape)
      {
        case 1: /*Etape 1*/
            while (!t->finish()){
                usleep(50000);
              avancer_all_Zone1(t);
            }
            cout<<">> fin thread zone 1"<<endl;
            break;

        case 2: /*Etape 2*/
            {
            /*récupération contexte suite*/
            map<string,sem_t*> *map_mutex; //map de toutes les sémaphores
            sem_t *my_sem,*sem_Zone2,*sem_Zone3,*sem_Zone4; //semaphore des zones 

            if (c->map_sem!=nullptr)
                map_mutex=c->map_sem;
            else
            {
                cerr<<"Problème de récupération de la map"<<endl;
                exit(1);
            }    
            
            map<string,sem_t*>::iterator it1=map_mutex->find("Zone1");
            map<string,sem_t*>::iterator it2=map_mutex->find("Zone2");
            map<string,sem_t*>::iterator it3=map_mutex->find("Zone3");
            map<string,sem_t*>::iterator it4=map_mutex->find("Zone4");
            if ((it1!=map_mutex->end())
                 && (it2!=map_mutex->end())
                 && (it3!=map_mutex->end())
                 && (it4!=map_mutex->end()))
            {
                my_sem= map_mutex->find("Zone1")->second;
                sem_Zone2= map_mutex->find("Zone2")->second;
                sem_Zone3= map_mutex->find("Zone3")->second;
                sem_Zone4= map_mutex->find("Zone4")->second;
            }else{
                cerr<<"Recherche d'un élément inéxistant dans la map"<<endl;
                exit(1);
            }

            /*ACTIONS*/
            while(!t->finish())
            {
                
                for(int i = 0; i < t->liste_personnes.size(); i++){
                    usleep(500);
                    personne& p=t->liste_personnes.at(i);
                    if(isOnZone1(p))
                    {
                        if(sem_wait(my_sem)==-1) //j'attends que ma partie soit dispo au cas où une autre thread l'a prise
                        {
                            perror("sem_wait() in mythread.cpp");
                            exit(1);
                        }

                        t->avancer(p);

                        if(sem_post(my_sem)==-1) //je libère ma zone
                        {
                            perror("sem_post()");
                            exit(1);
                        }
                    }
                }
            }
            

            /*je signale à la barrière que je suis devant*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }

            cout<<">> fin thread zone Zone1"<<endl;    
            break;
        }
        case 3:
            Moniteur* moniteur=c->m;
            while(!t->finish()){
                for(int i = 0; i < t->liste_personnes.size(); i++){
                    personne& p=t->liste_personnes.at(i);
                    if(isOnZone1(p))
                    {
                        if(pthread_mutex_lock(&(moniteur->mutex))!=0){
                            perror("pthread_mutex_lock");
                        }
                        while(!moniteur->cond+0) wait();//cond+0 condition NE
                        t->avancer(p);
                        //notify all
                        //unlock
                        //si proche d'une zone faire faire pareil avec cond différent
                    }
                }
            }
            
            /*thread arrivé à son terme (devant la barrière)*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }
            cout<<">> fin thread zone 1"<<endl; 
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
void *thread_avancerZone2(void *p_data){
  cout<<">> lancement thread zone 2"<<endl; 
  if (p_data != nullptr){
      
    Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
    terrain* t=c->t;
    //on va s'occuper uniquement des personnes qui sont dans la zone Nord-Ouest
    switch(c->_etape){
    case 1:

        while (!t->finish()){
            usleep(50000);
            avancer_all_Zone2(t);
        }
        cout<<">> fin thread zone 2"<<endl;
        break;

    case 2:
        /*récupération contexte suite*/
    {
        map<string,sem_t*> *map_mutex; //map de toutes les sémaphores
        sem_t *my_sem,*sem_Zone1,*sem_Zone3,*sem_Zone4; //semaphore des zones 

        if (c->map_sem!=nullptr)
            map_mutex=c->map_sem;
        else
        {
            cerr<<"Problème de récupération de la map"<<endl;
            exit(1);
        }    
                

        map<string,sem_t*>::iterator it1=map_mutex->find("Zone1");
        map<string,sem_t*>::iterator it2=map_mutex->find("Zone2");
        map<string,sem_t*>::iterator it3=map_mutex->find("Zone3");
        map<string,sem_t*>::iterator it4=map_mutex->find("Zone4");
        if ((it1!=map_mutex->end())
             && (it2!=map_mutex->end())
             && (it3!=map_mutex->end())
             && (it4!=map_mutex->end()))
        {
            my_sem= map_mutex->find("Zone2")->second;
            sem_Zone1= map_mutex->find("Zone1")->second;
            sem_Zone3= map_mutex->find("Zone3")->second;
            sem_Zone4= map_mutex->find("Zone4")->second;
        }else{
            cerr<<"Recherche d'un élément inéxistant dans la map"<<endl;
            exit(1);
        }

        /*ACTIONS*/
        while(!t->finish())
        {

            for(int i = 0; i < t->liste_personnes.size(); i++){
                usleep(500);
                personne& p=t->liste_personnes.at(i);
                if(isOnZone2(p))
                {
                    if (p.near_Zone1())
                    {
                        if(sem_wait(sem_Zone1)==-1) //j'attends que cette partie soit libre
                        {
                            perror("sem_wait() in mythread.cpp");
                            exit(1);
                        }
                        t->avancer(p);

                        if(sem_post(sem_Zone1)==-1) //je libère
                        {
                            perror("sem_post()");
                            exit(1);
                        }
                    }else{

                        if(sem_wait(my_sem)==-1) //j'attends que ma partie soit dispo au cas où une autre thread l'a prise
                        {
                            perror("sem_wait() in mythread.cpp");
                            exit(1);
                        }

                        t->avancer(p);

                        if(sem_post(my_sem)==-1) //je libère ma zone
                        {
                            perror("sem_post()");
                            exit(1);
                        }
                    }
                }
            }
        }

            /*je signale à la barrière que je suis devant*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }

            cout<<">> fin thread zone 2"<<endl;}
            break;
        case 3:
            Moniteur* moniteur=c->m; //recuperation du moniteur
            
            /*thread arrivé à son terme (devant la barrière)*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }
            cout<<">> fin thread zone 2"<<endl;
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
void *thread_avancerZone3(void *p_data){
  cout<<">> lancement thread zone 3"<<endl;
  if (p_data != nullptr)
   {
      
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;
        //on va s'occuper uniquement des personnes qui sont dans la zone Sud-Est

        switch(c->_etape){
          case 1:

              while (!t->finish()){
                usleep(50000);
                avancer_all_Zone3(t);
              }
              cout<<">> fin thread zone 3"<<endl;
              break; 

          case 2:
            {
            /*récupération contexte suite*/
            map<string,sem_t*> *map_mutex; //map de toutes les sémaphores
            sem_t *my_sem,*sem_Zone1,*sem_Zone2,*sem_Zone4; //semaphore des zones 

            if (c->map_sem!=nullptr)
                map_mutex=c->map_sem;
            else
            {
                cerr<<"Problème de récupération de la map"<<endl;
                exit(1);
            }    
            
            map<string,sem_t*>::iterator it1=map_mutex->find("Zone1");
            map<string,sem_t*>::iterator it2=map_mutex->find("Zone2");
            map<string,sem_t*>::iterator it3=map_mutex->find("Zone3");
            map<string,sem_t*>::iterator it4=map_mutex->find("Zone4");
            if ((it1!=map_mutex->end())
                 && (it2!=map_mutex->end())
                 && (it3!=map_mutex->end())
                 && (it4!=map_mutex->end()))
            {
                my_sem= map_mutex->find("Zone3")->second;
                sem_Zone1= map_mutex->find("Zone1")->second;
                sem_Zone2= map_mutex->find("Zone2")->second;
                sem_Zone4= map_mutex->find("Zone4")->second;
            }else{
                cerr<<"Recherche d'un élément inéxistant dans la map"<<endl;
                exit(1);
            }

            /*ACTIONS*/
            while(!t->finish())
            {

                for(int i = 0; i < t->liste_personnes.size(); i++){
                    usleep(500);
                    personne& p=t->liste_personnes.at(i);
                    if(isOnZone3(p))
                    {
                        if (p.near_Zone2())
                        {
                            if(sem_wait(sem_Zone2)==-1) //j'attends que cette partie soit libre
                            {
                                perror("sem_wait() in mythread.cpp");
                                exit(1);
                            }
                            t->avancer(p);

                            if(sem_post(sem_Zone2)==-1) //je libère
                            {
                                perror("sem_post()");
                                exit(1);
                            }
                        }else{

                            if(sem_wait(my_sem)==-1) //j'attends que ma partie soit dispo au cas où une autre thread l'a prise
                            {
                                perror("sem_wait() in mythread.cpp");
                                exit(1);
                            }

                            t->avancer(p);

                            if(sem_post(my_sem)==-1) //je libère ma zone
                            {
                                perror("sem_post()");
                                exit(1);
                            }
                        }
                    }
                }
            }

            /*je signale à la barrière que je suis devant*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }

            cout<<">> fin thread zone 3"<<endl;           
            break;
        }
        case 3:
            /*thread arrivé à son terme (devant la barrière)*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }
            cout<<">> fin thread zone 3"<<endl; 
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
void *thread_avancerZone4(void *p_data){
  cout<<">> lancement thread zone Sud-Ouest"<<endl;
  if (p_data != nullptr)
   {
      
        Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
        terrain* t=c->t;
        //on va s'occuper uniquement des personnes qui sont dans la zone 4

        switch(c->_etape){
          case 1:
              while (!t->finish()){
                usleep(50000);
                avancer_all_Zone4(t);
              }
              cout<<">> fin thread zone 4"<<endl;
              break;
          case 2:
            /*récupération contexte suite*/
            {
            map<string,sem_t*> *map_mutex; //map de toutes les sémaphores
            sem_t *my_sem,*sem_Zone1,*sem_Zone2,*sem_Zone3; //semaphore des zones 

            if (c->map_sem!=nullptr)
                map_mutex=c->map_sem;
            else
            {
                cerr<<"Problème de récupération de la map"<<endl;
                exit(1);
            }    
            
            map<string,sem_t*>::iterator it1=map_mutex->find("Zone1");
            map<string,sem_t*>::iterator it2=map_mutex->find("Zone2");
            map<string,sem_t*>::iterator it3=map_mutex->find("Zone3");
            map<string,sem_t*>::iterator it4=map_mutex->find("Zone4");
            if ((it1!=map_mutex->end())
                 && (it2!=map_mutex->end())
                 && (it3!=map_mutex->end())
                 && (it4!=map_mutex->end()))
            {
                my_sem= map_mutex->find("Zone4")->second;
                sem_Zone1= map_mutex->find("Zone1")->second;
                sem_Zone2= map_mutex->find("Zone2")->second;
                sem_Zone3= map_mutex->find("Zone3")->second;
            }else{
                cerr<<"Recherche d'un élément inéxistant dans la map"<<endl;
                exit(1);
            }

            /*ACTIONS*/
            while(!t->finish())
            {

                for(int i = 0; i < t->liste_personnes.size(); i++){
                    usleep(500);
                    personne& p=t->liste_personnes.at(i);
                    if(isOnZone4(p))
                    {
                        if (p.near_Zone3())
                        {
                            if(sem_wait(sem_Zone3)==-1) //j'attends que cette partie soit libre
                            {
                                perror("sem_wait() in mythread.cpp");
                                exit(1);
                            }
                            t->avancer(p);

                            if(sem_post(sem_Zone3)==-1) //je libère
                            {
                                perror("sem_post()");
                                exit(1);
                            }
                        }else{

                            if(sem_wait(my_sem)==-1) //j'attends que ma partie soit dispo au cas où une autre thread l'a prise
                            {
                                perror("sem_wait() in mythread.cpp");
                                exit(1);
                            }

                            t->avancer(p);

                            if(sem_post(my_sem)==-1) //je libère ma zone
                            {
                                perror("sem_post()");
                                exit(1);
                            }
                        }
                    }
                }
            }

            /*je signale à la barrière que je suis devant*/
            if (c->barrier!=nullptr)
            {
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }
            cout<<">> fin thread zone 4"<<endl;         
            break;
        }
        case 3:
            /*thread arrivé à son terme (devant la barrière)*/
            if(c->barrier!=nullptr){
              c->barrier->await();
            }else{
              cout<<">> probleme de récupération de la barrière"<<endl;
              exit(1);
            }

            cout<<">> fin thread zone 4"<<endl;
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
      
      Contexte* c=(Contexte*) p_data;// recuperation du contexte applicatif
      terrain my_terrain=*(c->t);
      personne my_personne=*(c->_pers);
      switch(c->_etape){
        case 1:

            while(!my_personne.aFini())
              my_terrain.avancer(my_personne);
            break;
        case 2:
            {
              sem_t* mutex=c->mutex;
              if (c->barrier!=nullptr){
                  CyclicBarrier* barrier=c->barrier;
              
                  while(!my_personne.aFini())
                  {
                    usleep(5000);
                    if(sem_wait(mutex)==-1) //j'attends que le terrain soit disponible
                    {
                      perror("sem_wait() in mythread.cpp");
                      exit(1);
                    }
                    my_terrain.avancer(my_personne);
                    if(sem_post(mutex)==-1)// je rends le terrain
                    {
                        perror("sem_post()");
                        exit(1);
                    }
                  }


                  // je signale que je suis devant la barrière avant de sortir
                  barrier->await();
              }else{
                  cerr<<"problème de récupération de la barrière (-t2)"<<endl;
              }
              break;
          }
        case 3:
            /*récupération barrière*/
            if (c->barrier!=nullptr){
                CyclicBarrier* barrier=c->barrier;

                /*récupération Moniteur*/
                Moniteur* moniteur=c->m;

                while(!my_personne.aFini()){
                    pthread_mutex_lock(&(moniteur->mutex));
                    if(!(moniteur->available)) pthread_cond_wait(moniteur->cond, &(moniteur->mutex)); 
                    my_terrain.avancer(my_personne);
                    pthread_cond_signal(moniteur->cond);
                    pthread_mutex_unlock(&(moniteur->mutex));
                }
                barrier->await();
            }else{
                cerr<<"problème de récupération de la barrière (-t2)"<<endl;
            }
            break;

      }


  }else{
    cerr<< "problème dans la récupération du contexte applicatif du thread (-t2): sortie du programme"<<endl;
    exit(1);
  }
}

/*definition des fonctions*/

/*
 * Permet de determiner si une personne est dans la zone 1
 */
bool isOnZone1(personne p){
  return p.getZone() == 1;
}
/*
 * Permet de determiner si une personne est dans la zone 2
 */
bool isOnZone2(personne p){;
  return p.getZone() == 2;
}

/*
 * Permet de determiner si une personne est dans la zone 3
 */
bool isOnZone3(personne p){
  return p.getZone() == 3;
}

/*
 * Permet de determiner si une personne est dans la zone 4
 */
bool isOnZone4(personne p){
  return p.getZone() == 4;
}


/*
 * Fait avancer toutes les personnes présentes dans la zone SO
 */
void avancer_all_Zone1(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnZone1(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone SE
 */
void avancer_all_Zone2(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnZone2(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone NE
 */
void avancer_all_Zone3(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnZone3(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}

/*
 * Fait avancer toutes les personnes présentes dans la zone NO
 */
void avancer_all_Zone4(terrain *t){
    
    for(int i = 0; i < t->liste_personnes.size(); i++){
      if(isOnZone4(t->liste_personnes.at(i)))
        t->avancer(t->liste_personnes.at(i));
    }
}




//-----------------------------
//          etape 2
//-----------------------------
void avancer_Zone1_moniteur(terrain* t,personne* p){}
void avancer_Zone2_moniteur(terrain* t,personne* p){}
void avancer_Zone3_moniteur(terrain* t,personne* p){}
void avancer_Zone4_moniteur(terrain* t,personne* p){}