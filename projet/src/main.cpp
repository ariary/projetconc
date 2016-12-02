/*
 *
 * File: main.cpp
 * Author: Adrien Prestini & Antoine Rabenandrasana
 * 
 * Version: dernier rendu
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "include/terrain.h"
#include "include/mythreads.h"
#include "include/contexte.h"
#include "include/graphique.h"
#include "include/Moniteur.h"
#include  <iostream>
#include <getopt.h>
#include <sys/resource.h> //getrusage
#include <math.h> //pow
#include <pthread.h>
#include <semaphore.h> //utilisation sémarphore
#include <unistd.h>



using namespace std;

int main(int argc, char *argv[]){
    
    
    /*-m*/
    struct rusage r_usage;
    clock_t tempsDebut, tempsFin;
    struct timeval utime;
    struct timeval stime;
    time_t begin,end;
    

    /*prise en charge des arguments*/
    int nb_personne=2;
    int nb_thread;
    int num_etape=2;
    bool time_execution=false;
    int opt;
    while ((opt = getopt(argc , argv, "mp:t:e:")) != -1){
        switch (opt) {
        case 'e':
            if (optarg)
                num_etape=atoi(optarg);
            else{
                std::cerr<< "Problème d'arguments -e[1..3]!"<<std::endl;
                exit(EXIT_FAILURE);
            }
        case 'm':
          time_execution=true;
          break;
        case 'p':
            if (optarg)
                nb_personne=atoi(optarg);
            else{
                std::cerr<< "Problème d'arguments -p[0..9]!"<<std::endl;
                exit(EXIT_FAILURE);
            }
          break;
        case 't':
            if (optarg)
                nb_thread=atoi(optarg);
            else{
                std::cerr << "Problème d'arguments -t[012]!"<<std::endl;
                exit(EXIT_FAILURE);
            }
          break;
        case '?':
          printf("/!\\ Option inconnue\n");
          break;
        }
    }      

    printf("\n>>Execution de l'étape %d: nb de personne %d; scénario de threads %d; ",num_etape, (int)pow(2,nb_personne), nb_thread);
    (time_execution)?printf("Avec mesure de temps\n\n"):printf("sans mesure de temps\n\n");
    tempsDebut = clock();
    begin= time(NULL);



    /*lancement du programme*/
    terrain t = terrain((int)pow(2,nb_personne)) ;
#ifdef GRAPH
    pthread_t tGraph;
    if(pthread_create(&tGraph, NULL, afficher, &t)!=0)
    {
        perror("pthread_create() du graphe");
        exit(1);
    }

#endif
    if (nb_thread==0)
    {
        Contexte my_contexte(1,&t);
        pthread_t t0;
        

        if(pthread_create(&t0, NULL, thread_avancerALL, &my_contexte)!=0)
        {
            perror("pthread_create()");
            exit(1);
        }
         

        if(pthread_join(t0, NULL)!=0)
        {
            perror("pthread_join()");
            exit(1);
        }

        
    }else if(nb_thread==1){
        pthread_t t1; //zone1
        pthread_t t2; //zone2
        pthread_t t3; //Zone3
        pthread_t t4; //Zone4
        
        if (num_etape==1)
        {  //ETAPE 1

            Contexte my_contexte(1,&t);
            if(    (pthread_create(&t1, NULL, thread_avancerZone1, &my_contexte)!=0)
                || (pthread_create(&t2, NULL, thread_avancerZone2, &my_contexte)!=0)
                || (pthread_create(&t3, NULL, thread_avancerZone3, &my_contexte)!=0)
                || (pthread_create(&t4, NULL, thread_avancerZone4, &my_contexte)!=0))
            {
                perror("pthread_create()");
                exit(1);
            }
            
            if (  (pthread_join(t1, NULL))
                ||(pthread_join(t2, NULL))
                ||(pthread_join(t3, NULL))
                ||(pthread_join(t4, NULL)))
            {
                perror("pthread_join()");
                exit(1);
            }
        }else if(num_etape==2){
            //ETAPE 2               
            /*Initialisation d'une sémaphore par zone*/
            sem_t sem_Zone1,sem_Zone2,sem_Zone3,sem_Zone4;
            if(   (sem_init(&sem_Zone1, 0, 1)==-1)
                ||(sem_init(&sem_Zone2, 0, 1)==-1)
                ||(sem_init(&sem_Zone3, 0, 1)==-1)
                ||(sem_init(&sem_Zone4, 0, 1)==-1) )
            {
                perror("sem_init()");
                exit(1);
            }

            /*Insertion des semaphore dans la map*/
            map<string,sem_t*> m_sem;
            m_sem.insert (pair<string,sem_t*>("Zone1",&sem_Zone1) );
            m_sem.insert (pair<string,sem_t*>("Zone2",&sem_Zone2) );
            m_sem.insert (pair<string,sem_t*>("Zone3",&sem_Zone3) );
            m_sem.insert (pair<string,sem_t*>("Zone4",&sem_Zone4) );


            /*Initialisation Cyclicbarrier pour attendre la fin des threads*/
            CyclicBarrier barrier(4);

            /*Initialisation du Contexte*/
            Contexte my_contexte(2,&t,&m_sem);
            my_contexte.setCyclicBarrier(&barrier);

            /*lancement des threads*/
            if(    (pthread_create(&t1, NULL, thread_avancerZone1, &my_contexte)!=0)
                || (pthread_create(&t2, NULL, thread_avancerZone2, &my_contexte)!=0)
                || (pthread_create(&t3, NULL, thread_avancerZone3, &my_contexte)!=0)
                || (pthread_create(&t4, NULL, thread_avancerZone4, &my_contexte)!=0))
            {
                perror("pthread_create()");
                exit(1);
            }
            
            /*Appel bloquant de la barrière tant que tous les threads ne sont pas terminés*/
            barrier.block();

            /*destruction des sémaphores*/
            if ((sem_destroy(&sem_Zone4)==-1)
                ||(sem_destroy(&sem_Zone3)==-1)
                ||(sem_destroy(&sem_Zone2)==-1)
                ||(sem_destroy(&sem_Zone1)==-1))
            {
                perror("sem_destroy()");
                exit(1);
            }
        }else{ // -t1 -e3
            /*Initialisation du moniteur*/
            //condition
            pthread_cond_t zone1;
            pthread_cond_t zone2;
            pthread_cond_t zone3;
            pthread_cond_t zone4;
            //Tableau de conditions
            pthread_cond_t cond[4];
            cond[0]=zone1;cond[1]=zone2;cond[2]=zone3;cond[3]=zone4;

            CyclicBarrier barrier(4);


            //mutex & Moniteur
            pthread_mutex_t lock;
            if (pthread_mutex_init(&lock, NULL) != 0)
            {
                cout<<">> initialisation du mutex échouée"<<endl;
                return 1;
            }
            Moniteur my_moniteur(cond,lock);

            /*initialisation du contexte*/
            Contexte my_contexte(3,&t);
            my_contexte.setMoniteur(&my_moniteur);
            my_contexte.setCyclicBarrier(&barrier);


            /*Lancement des threads*/
            if((pthread_create(&t1, NULL, thread_avancerZone1, &my_contexte)!=0)
              ||(pthread_create(&t2, NULL, thread_avancerZone2, &my_contexte)!=0)
              ||(pthread_create(&t3, NULL, thread_avancerZone3, &my_contexte)!=0)
              ||(pthread_create(&t4, NULL, thread_avancerZone4, &my_contexte)!=0))
            {
                perror("pthread_create()");
                exit(1);
            }


            /*attente de la fin des threads*/
            barrier.block();

            cout<<">> Tous les threads sont terminés (-t1)"<<endl;

        }

    }else{//nb_thread=2

        if (num_etape==1)
        {   //ETAPE 1

            Contexte my_contexte(1,&t);
            vector<pthread_t> v_thread; //création pour l'attente des threads
            /*On lance un thread par personne */
            cout<<">> lancement d'un thread par personne (-t2)"<<endl;
            usleep(5000);
            for (int i = 0; i < t.liste_personnes.size(); ++i)
            {
                pthread_t th_personne;
                my_contexte._pers=&(t.liste_personnes[i]);
                v_thread.push_back(th_personne);
                if (pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte)!=0)
                {
                    perror("pthread_create()");
                    exit(1);
                }
                
                
            }
            cout<<">> tous les threads sont lancés (-t2)"<<endl;

            /*On attend la fin de chaque thread */
            int wait_t=(int)pow(2,nb_personne);
            cout<<">> attente de "<<wait_t<<"  threads"<<endl;
            for (pthread_t t : v_thread)
            {
                if (pthread_join(t, NULL))
                {
                    perror("pthread_join()");
                    exit(1);
                }
                cout<<">> attente de "<<--wait_t<<"  threads"<<endl;
                
            }
        }else if(num_etape==2){
            //ETAPE2

            sem_t sem_terrain;
            if(sem_init(&sem_terrain, 0, 1)==-1)
            {
                perror("sem_init()");
                exit(1);
            }     

            /*Contexte commun*/
            CyclicBarrier barrier(pow(2,nb_personne));
            Contexte my_contexte(2,&t);
            my_contexte.setSemaphore(&sem_terrain);         
            my_contexte.setCyclicBarrier(&barrier);

            /*On lance un thread par personne */
            for (int i = 0; i < t.liste_personnes.size(); ++i)
            {

                //Mise en place contexe
                my_contexte.setPersonne(&(t.liste_personnes[i]));

                //lancement thread
                pthread_t th_personne;
                
                if (pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte)!=0)
                {
                    perror("pthread_create()");
                    exit(1);
                }
                
            }
            cout<<">> Début de l'attente"<<endl;

            barrier.block();//appel bloquant
            cout<<">> Tous les threads sont terminés (-t2)"<<endl;
           
        }else if (num_etape==3)
        {
            CyclicBarrier barrier(pow(2,nb_personne));
            //mutex & Moniteur
            pthread_mutex_t lock;
            if (pthread_mutex_init(&lock, NULL) != 0)
            {
                cout<<">> initialisation du mutex échouée"<<endl;
                return 1;
            }
            pthread_cond_t cond;
            Moniteur my_moniteur(&cond,lock);



            Contexte my_contexte(3,&t);
            my_contexte.setMoniteur(&my_moniteur);     
            my_contexte.setCyclicBarrier(&barrier);

            /*On lance un thread par personne */
            for (int i = 0; i < t.liste_personnes.size(); ++i)
            {

                //Mise en place contexe
                my_contexte.setPersonne(&(t.liste_personnes[i]));

                //lancement thread
                pthread_t th_personne;
                
                if (pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte)!=0)
                {
                    perror("pthread_create()");
                    exit(1);
                }
                
            }
            cout<<">> Début de l'attente"<<endl;
            barrier.block();//appel bloquant
            cout<<">> Tous les threads sont terminés (-t2)"<<endl;
        }
    }   
#ifdef GRAPH
    if(pthread_join(tGraph, NULL)!=0)
    {
        perror("pthread_join() graphique");
        exit(1);
    }
#endif
    tempsFin = clock();
    end = time(NULL);
    if (time_execution)
    {
        //empreinte prgm
        getrusage(RUSAGE_SELF,&r_usage);
        utime = r_usage.ru_utime;
        stime = r_usage.ru_stime;
        printf("\nEmpreinte maximale du programme: %ld\n",r_usage.ru_maxrss);
        //temps réel
        printf("Temps de réponse: %.3lf s\n", (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC);
        //temps CPU
        int64_t tmps_CPU_sec=utime.tv_sec+stime.tv_sec+stime.tv_sec;
        int64_t tmps_CPU_usec =utime.tv_usec+stime.tv_sec+stime.tv_usec;
        printf("Temps CPU: %ld.%06ld s\n", tmps_CPU_sec,tmps_CPU_usec);

    }
    return 0;

}