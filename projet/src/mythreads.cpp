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
            /*thread arrivé à son terme (devant la barrière)*/
            if (c->m!=nullptr)
            {   
                //récupération moniteur et paire de la zone 1
                Moniteur* moniteur=c->m;
                pair <pthread_mutex_t,pthread_cond_t>& pr1=moniteur->pr_zone1;

                while(!t->finish()){
                    for(int i = 0; i < t->liste_personnes.size(); i++){
                        usleep(500);
                        personne& p=t->liste_personnes.at(i);
                        
                        //p.print_personne();
                        if(isOnZone1(p))
                        {
                            //LOCK1
                            if (pthread_mutex_lock(&(pr1.first)))
                            {
                                perror("(-t1) pthread_mutex_lock");
                                exit(1);
                            }
                            //WHILE(!COND1) WAIT()
                            while(!(moniteur->available1)){
                                if (pthread_cond_wait(&(pr1.second), &(pr1.first))!=0)
                                {
                                    perror("(-t2) pthread_cond_wait");
                                    exit(1);
                                }
                            }
                            //SIGNAL1
                            if(pthread_cond_signal(&(pr1.second))!=0){
                                perror("(-t1) pthread_cond_signal");
                                exit(1);
                            }
                            t->avancer(p);
                            //UNLOCK1
                            if (pthread_mutex_unlock(&(pr1.first)))
                            {
                                perror("(-t1) pthread_cond_unlock");
                                exit(1);
                            }
                        }
                    }
                }
            }else{
                cout<<">> probleme de récupération du moniteur"<<endl;
                exit(1); 
            }

            /*je signale à la barrière que je suis arrivé*/
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
            /*thread arrivé à son terme (devant la barrière)*/
            if (c->m!=nullptr)
            {   
                //récupération moniteur et paire de la zone 1 et 2
                Moniteur* moniteur=c->m;
                pair <pthread_mutex_t,pthread_cond_t>& pr2=moniteur->pr_zone2;
                pair <pthread_mutex_t,pthread_cond_t>& pr1=moniteur->pr_zone1;

                while(!t->finish()){
                    for(int i = 0; i < t->liste_personnes.size(); i++){
                        usleep(500);
                        personne& p=t->liste_personnes.at(i);
                        if(isOnZone2(p))
                        {
                            //LOCK2
                            if (pthread_mutex_lock(&(pr2.first)))
                            {
                                perror("(-t1) pthread_mutex_lock");
                                exit(1);
                            }
                            //WHILE(!COND2) WAIT()
                            while(!(moniteur->available2)){
                                if (pthread_cond_wait(&(pr2.second), &(pr2.first))!=0)
                                {
                                    perror("(-t2) pthread_cond_wait");
                                    exit(1);
                                }
                            }
                            //SI JE SUIS PRET DE 1
                            if (p.near_Zone1())
                            {
                                //LOCK1
                                if (pthread_mutex_lock(&(pr1.first)))
                                {
                                    perror("(-t1) pthread_mutex_lock");
                                    exit(1);
                                }
                                //WHILE(!COND1) WAIT()
                                while(!(moniteur->available1)){
                                    if (pthread_cond_wait(&(pr1.second), &(pr1.first))!=0)
                                    {
                                        perror("(-t1) pthread_cond_wait");
                                        exit(1);
                                    }
                                }
                                //SIGNAL1
                                if(pthread_cond_signal(&(pr1.second))!=0){
                                    perror("(-t1) pthread_cond_signal");
                                    exit(1);
                                }
                                //UNLOCK1
                                if (pthread_mutex_unlock(&(pr1.first)))
                                {
                                    perror("(-t1) pthread_cond_unlock");
                                    exit(1);
                                }
                            }
                            t->avancer(p);
                            //SIGNAL2
                            if(pthread_cond_signal(&(pr2.second))!=0){
                                perror("(-t1) pthread_cond_signal");
                                exit(1);
                            }
                            //UNLOCK2
                            if (pthread_mutex_unlock(&(pr2.first)))
                            {
                                perror("(-t1) pthread_cond_unlock");
                                exit(1);
                            }
                        }
                    }
                }
            }else{
                cout<<">> probleme de récupération du moniteur"<<endl;
                exit(1); 
            }

            /*je signale à la barrière que je suis arrivé*/
            if(c->barrier!=nullptr){
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
            if (c->m!=nullptr)
            {   
                //récupération moniteur et paire de la zone 2 et 3
                Moniteur* moniteur=c->m;
                pair <pthread_mutex_t,pthread_cond_t>& pr3=moniteur->pr_zone3;
                pair <pthread_mutex_t,pthread_cond_t>& pr2=moniteur->pr_zone2;

                while(!t->finish()){
                    for(int i = 0; i < t->liste_personnes.size(); i++){
                        usleep(500);
                        personne& p=t->liste_personnes.at(i);
                        if(isOnZone3(p))
                        {
                            //LOCK3
                            if (pthread_mutex_lock(&(pr3.first)))
                            {
                                perror("(-t1) pthread_mutex_lock");
                                exit(1);
                            }
                            //WHILE(!COND3) WAIT()
                            while(!(moniteur->available3)){
                                if (pthread_cond_wait(&(pr3.second), &(pr3.first))!=0)
                                {
                                    perror("(-t2) pthread_cond_wait");
                                    exit(1);
                                }
                            }
                            //SI JE SUIS PRET DE 2
                            if (p.near_Zone2())
                            {
                                //LOCK2
                                if (pthread_mutex_lock(&(pr2.first)))
                                {
                                    perror("(-t1) pthread_mutex_lock");
                                    exit(1);
                                }
                                //WHILE(!COND2) WAIT()
                                while(!(moniteur->available2)){
                                    if (pthread_cond_wait(&(pr2.second), &(pr2.first))!=0)
                                    {
                                        perror("(-t1) pthread_cond_wait");
                                        exit(1);
                                    }
                                }
                                //SIGNAL2
                                if(pthread_cond_signal(&(pr2.second))!=0){
                                    perror("(-t1) pthread_cond_signal");
                                    exit(1);
                                }
                                //UNLOCK2
                                if (pthread_mutex_unlock(&(pr2.first)))
                                {
                                    perror("(-t1) pthread_cond_unlock");
                                    exit(1);
                                }
                            }
                            t->avancer(p);
                            //SIGNAL3
                            if(pthread_cond_signal(&(pr3.second))!=0){
                                perror("(-t1) pthread_cond_signal");
                                exit(1);
                            }
                            //UNLOCK3
                            if (pthread_mutex_unlock(&(pr3.first)))
                            {
                                perror("(-t1) pthread_cond_unlock");
                                exit(1);
                            }
                        }
                    }
                }
            }else{
                cout<<">> probleme de récupération du moniteur"<<endl;
                exit(1); 
            }

            /*je signale à la barrière que je suis arrivé*/
            if(c->barrier!=nullptr){
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
  cout<<">> lancement thread zone 4"<<endl;
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
            if (c->m!=nullptr)
            {   
                //récupération moniteur et paire de la zone 3 et 4
                Moniteur* moniteur=c->m;
                pair <pthread_mutex_t,pthread_cond_t>& pr4=moniteur->pr_zone4;
                pair <pthread_mutex_t,pthread_cond_t>& pr3=moniteur->pr_zone3;

                while(!t->finish()){
                    for(int i = 0; i < t->liste_personnes.size(); i++){
                        usleep(500);
                        personne& p=t->liste_personnes.at(i);
                        if(isOnZone4(p))
                        {
                            //LOCK4
                            if (pthread_mutex_lock(&(pr4.first)))
                            {
                                perror("(-t1) pthread_mutex_lock");
                                exit(1);
                            }

                            //WHILE(!COND4) WAIT()
                            while(!(moniteur->available4)){
                                if (pthread_cond_wait(&(pr4.second), &(pr4.first))!=0)
                                {
                                    perror("(-t2) pthread_cond_wait");
                                    exit(1);
                                }
                            }
                            //SI JE SUIS PRET DE 3
                            if (p.near_Zone3())
                            {
                                //LOCK3
                                if (pthread_mutex_lock(&(pr3.first)))
                                {
                                    perror("(-t1) pthread_mutex_lock");
                                    exit(1);
                                }
                                //WHILE(!COND3) WAIT()
                                while(!(moniteur->available3)){
                                    if (pthread_cond_wait(&(pr3.second), &(pr3.first))!=0)
                                    {
                                        perror("(-t1) pthread_cond_wait");
                                        exit(1);
                                    }
                                }
                                //SIGNAL3
                                if(pthread_cond_signal(&(pr3.second))!=0){
                                    perror("(-t1) pthread_cond_signal");
                                    exit(1);
                                }
                                //UNLOCK3
                                if (pthread_mutex_unlock(&(pr3.first)))
                                {
                                    perror("(-t1) pthread_cond_unlock");
                                    exit(1);
                                }
                            }
                            t->avancer(p);
                            //SIGNAL4
                            if(pthread_cond_signal(&(pr4.second))!=0){
                                perror("(-t1) pthread_cond_signal");
                                exit(1);
                            }
                            //UNLOCK4
                            if (pthread_mutex_unlock(&(pr4.first)))
                            {
                                perror("(-t1) pthread_cond_unlock");
                                exit(1);
                            }
                        }
                    }
                }
            }else{
                cout<<">> probleme de récupération du moniteur"<<endl;
                exit(1); 
            }

            /*je signale à la barrière que je suis arrivé*/
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
                int i=100;
                while(!my_personne.aFini()){
                    //LOCK
                    if (pthread_mutex_lock(&(moniteur->mutex)))
                    {
                        perror("(-t2) pthread_mutex_lock");
                        exit(1);
                    }
                    //WHILE(!COND) WAIT()
                    while(!(moniteur->available)){
                        if (pthread_cond_wait(moniteur->cond, &(moniteur->mutex))!=0)
                        {
                            perror("(-t2) pthread_cond_wait");
                            exit(1);
                        }
                    }
                    my_terrain.avancer(my_personne);
                    if(i==0){my_personne.print_personne(); i=100;}
                    //SIGNAL()
                    if(pthread_cond_signal(moniteur->cond)!=0){
                        perror("(-t2) pthread_cond_signal");
                        exit(1);
                    }
                    //UNLOCK
                    if (pthread_mutex_unlock(&(moniteur->mutex)))
                    {
                        perror("(-t2) pthread_cond_unlock");
                        exit(1);
                    }
                    i--;
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