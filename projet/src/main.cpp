/*
 *
 * File: main.cpp
 * Author: Adrien Prestini & Antoine Rabenandrasana
 * 
 * Version: rendu du 10 octobre 2016
 * Moidifications: rencu du 7 novembre 2016
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "include/terrain.h"
#include "include/mythreads.h"
#include "include/contexte.h"
#include  <iostream>
#include <getopt.h>
#include <sys/resource.h> //getrusage
#include <math.h> //pow
#include <pthread.h>
#include <semaphore.h> //utilisation sémarphore


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
            pthread_t t1; //NE
            pthread_t t2; //NO
            pthread_t t3; //SE
            pthread_t t4; //SO

            if (num_etape==1)
            {  //ETAPE 1

                Contexte my_contexte(1,&t);

                if(    (pthread_create(&t1, NULL, thread_avancerNE, &my_contexte)!=0)
                    || (pthread_create(&t2, NULL, thread_avancerNO, &my_contexte)!=0)
                    || (pthread_create(&t3, NULL, thread_avancerSE, &my_contexte)!=0)
                    || (pthread_create(&t4, NULL, thread_avancerSO, &my_contexte)!=0))
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
                sem_t sem_NO,sem_SE,sem_SO,sem_NE;
                if(   (sem_init(&sem_NO, 0, 1)==-1)
                    ||(sem_init(&sem_SE, 0, 1)==-1)
                    ||(sem_init(&sem_SO, 0, 1)==-1)
                    ||(sem_init(&sem_NE, 0, 1)==-1) )
                {
                    perror("sem_init()");
                    exit(1);
                }

                /*Insertion des semaphore dans la map*/
                map<string,sem_t*> m_sem;
                m_sem.insert (pair<string,sem_t*>("NO",&sem_NO) );
                m_sem.insert (pair<string,sem_t*>("SE",&sem_SE) );
                m_sem.insert (pair<string,sem_t*>("SO",&sem_SO) );
                m_sem.insert (pair<string,sem_t*>("NE",&sem_NE) );



                /*Initialisation des sémaphores utiles pour attendre la fin des threads*/
                //NO
                sem_t join_NO;
                if(sem_init(&join_NO, 0, 0)) //sémaphore privée
                {
                    perror("sem_init()");
                    exit(1);
                }

                //SO
                sem_t join_SO;
                if(sem_init(&join_SO, 0, 0)) //sémaphore privée
                {
                    perror("sem_init()");
                    exit(1);
                }


                //NE
                sem_t join_NE;
                if(sem_init(&join_NE, 0, 0)) //sémaphore privée
                {
                    perror("sem_init()");
                    exit(1);
                }


                //SE
                sem_t join_SE;
                if(sem_init(&join_SE, 0, 0)) //sémaphore privée
                {
                    perror("sem_init()");
                    exit(1);
                }


                /*Initialisation des Contextes*/

                //NO
                Contexte contexte_NO(2,&t,&m_sem,&join_NO);
                //SO
                Contexte contexte_SO(2,&t,&m_sem,&join_SO);
                //NE
                Contexte contexte_NE(2,&t,&m_sem,&join_NE);
                //SE
                Contexte contexte_SE(2,&t,&m_sem,&join_SE);

                /*lancement des threads*/
                if(    (pthread_create(&t2, NULL, thread_avancerNE, &contexte_NO)!=0)
                    || (pthread_create(&t4, NULL, thread_avancerNO, &contexte_SO)!=0)
                    || (pthread_create(&t1, NULL, thread_avancerSE, &contexte_NE)!=0)
                    || (pthread_create(&t3, NULL, thread_avancerSO, &contexte_SE)!=0))
                {
                    perror("pthread_create()");
                    exit(1);
                }
                
                /*up sur les semaphore des threads (bis) logiquement bloqué si la thread est active*/
                if(   (sem_wait(&join_NO)==-1)
                    ||(sem_wait(&join_SO)==-1)
                    ||(sem_wait(&join_NE)==-1)
                    ||(sem_wait(&join_SE)==-1))
                {
                    perror("sem_wait() in main.cpp");
                    exit(1);
                }

                /*destruction des sémaphores*/
                if ((sem_destroy(&sem_NE)==-1)
                    ||(sem_destroy(&sem_SE)==-1)
                    ||(sem_destroy(&sem_NO)==-1)
                    ||(sem_destroy(&sem_SO)==-1)
                    ||(sem_destroy(&join_NO)==-1)
                    ||(sem_destroy(&join_SO)==-1)
                    ||(sem_destroy(&join_NE)==-1)
                    ||(sem_destroy(&join_SE)==-1))
                {
                    perror("sem_destroy()");
                    exit(1);
                }
            }else{ // -t1 -e3
                /*Initialisation du moniteur*/
                //condition
                pthread_cond_t zoneNE;
                pthread_cond_t zoneNO;
                pthread_cond_t zoneSO;
                pthread_cond_t zoneSE;
                //Tableau de conditions
                pthread_cond_t cond[4];
                cond[0]=zoneNE;cond[1]=zoneNO;cond[2]=zoneSO;cond[3]=zoneSE;
                //mutex
                pthread_mutex_t mutex;
                Moniteur my_moniteur(cond,mutex);

                Contexte my_contexte(1,&t);
                my_contexte.setMoniteur(&my_moniteur);




            }

        }else{//nb_thread=4

            if (num_etape==1)
            {   //ETAPE 1

                Contexte my_contexte(1,&t);
                vector<pthread_t> v_thread; //création pour l'attente des threads
                
                /*On lance un thread par personne */
                cout<<">> lancement d'un thread par personne (-t2)"<<endl;
                for (int i = 0; i < t.liste_personnes.size(); ++i)
                {
                    pthread_t th_personne;
                    my_contexte._pers=&(t.liste_personnes[i]);

                    if (pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte)!=0)
                    {
                        perror("pthread_create()");
                        exit(1);
                    }
                    
                    v_thread.push_back(th_personne);
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

                vector<sem_t*> v_private; //création pour l'attente des threads avec semaphores privées
                sem_t sem_terrain;
                if(sem_init(&sem_terrain, 0, 1)==-1)
                {
                    perror("sem_init()");
                    exit(1);
                }


                /*On lance un thread par personne */
                for (int i = 0; i < t.liste_personnes.size(); ++i)
                {

                    //Mise en place contexte
                    sem_t s_private;
                    if(sem_init(&s_private, 0, 0)) //sémaphore privée
                    {
                        perror("sem_init()");
                        exit(1);
                    }

                    v_private.push_back(&s_private);
                    Contexte my_contexte(2,&t,nullptr,&s_private,&(t.liste_personnes[i]));
                    my_contexte.mutex=&sem_terrain;

                    //lancement thread
                    pthread_t th_personne;

                    if (pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte)!=0)
                    {
                        perror("pthread_create()");
                        exit(1);
                    }
                    
                }
                cout<<">> Début de l'attente"<<endl;

                /*On attend la fin de chaque thread */ 
                int i=pow(2,nb_personne);              
                for (sem_t* s_private: v_private)
                {   
                    if (s_private!=nullptr)
                    {
                        if(sem_wait(s_private)==-1)
                        {
                            perror("sem_wait() in main.cpp");
                            exit(1);
                        }
                    }else{
                        break; //eviter segfault
                    }
                    cout<<">> attente de "<<i--<<" threads"<<endl;

                    if (sem_destroy(s_private)==-1)
                    {
                        perror("sem_destroy()");
                        exit(1);
                    }
                    v_private.pop_back();
                }
                cout<<">> Tous les threads sont terminés (-t2)"<<endl;
            }
        }   
    

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