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
          printf("pb \n");
          break;
        }
    }      

    printf("Execution de l'étape %d: nb de personne 2^%d; scénario de threads %d; ",num_etape, nb_personne, nb_thread);
    (time_execution)?printf("Avec mesure de temps\n\n"):printf("sans mesure de temps\n\n");
    tempsDebut = clock();
    begin= time(NULL);



    /*lancement du programme*/
    terrain t = terrain((int)pow(2,nb_personne)) ;





        if (nb_thread==0)
        {
            Contexte my_contexte(1,&t);
            pthread_t t0;
            pthread_create(&t0, NULL, thread_avancerALL, &my_contexte);
            pthread_join(t0, NULL);
            
        }else if(nb_thread==1){
            pthread_t t1; //NE
            pthread_t t2; //NO
            pthread_t t3; //SE
            pthread_t t4; //SO

            if (num_etape==1)
            {  //ETAPE 1

                Contexte my_contexte(1,&t);
                pthread_create(&t1, NULL, thread_avancerNE, &my_contexte);
                pthread_create(&t2, NULL, thread_avancerNO, &my_contexte);
                pthread_create(&t3, NULL, thread_avancerSE, &my_contexte);
                pthread_create(&t4, NULL, thread_avancerSO, &my_contexte);

                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                pthread_join(t3, NULL);
                pthread_join(t4, NULL);
            }else if(num_etape==2){
                //ETAPE 2
                
                /*Initialisation de la semaphore du terrain */
                sem_t sem_terrain;
                sem_init(&sem_terrain, 0, 1);

                /*Initialisartion des sémaphores utiles pour attendre la fin des threads*/
                //NO
                sem_t join_NO;
                sem_init(&join_NO, 0, 0); //sémaphore privée

                //SO
                sem_t join_SO;
                sem_init(&join_SO, 0, 0);

                //NE
                sem_t join_NE;
                sem_init(&join_NE, 0, 0);

                //SE
                sem_t join_SE;
                sem_init(&join_SE, 0, 0);

                /*Initialisation des Contextes*/

                //NO
                Contexte contexte_NO(2,&t,&sem_terrain,&join_NO);
                //SO
                Contexte contexte_SO(2,&t,&sem_terrain,&join_SO);
                //NE
                Contexte contexte_NE(2,&t,&sem_terrain,&join_NE);
                //SE
                Contexte contexte_SE(2,&t,&sem_terrain,&join_SE);

                /*lancement des threads*/
                pthread_create(&t2, NULL, thread_avancerNO, &contexte_NO);
                pthread_create(&t4, NULL, thread_avancerSO, &contexte_SO);
                pthread_create(&t1, NULL, thread_avancerNE, &contexte_NE);
                pthread_create(&t3, NULL, thread_avancerSE, &contexte_SE);
                
                /*up sur les semaphore des threads (bis) logiquement bloqué si la thread est active*/
                sem_wait(&join_NO);
                sem_wait(&join_SO);
                sem_wait(&join_NE);
                sem_wait(&join_SE);

                /*destruction des sémaphores*/
                sem_destroy(&sem_terrain);
                sem_destroy(&join_NO);
                sem_destroy(&join_SO);
                sem_destroy(&join_NE);
                sem_destroy(&join_SE);
            }

        }else{//nb_thread=4

            if (num_etape==1)
            {   //ETAPE 1

                Contexte my_contexte(1,&t);
                vector<pthread_t> v_thread; //création pour l'attente des threads
                
                /*On lance un thread par personne */
                for (int i = 0; i < t.liste_personnes.size(); ++i)
                {
                    pthread_t th_personne;
                    my_contexte._pers=&(t.liste_personnes[i]);
                    pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte);
                    v_thread.push_back(th_personne);
                }

                /*On attend la fin de chaque thread */
                for (pthread_t t : v_thread)
                {
                    pthread_join(t, NULL);
                }
            }else if(num_etape==2){
                    //ETAPE2

                vector<sem_t*> v_private; //création pour l'attente des threads avec semaphores privées
                sem_t sem_terrain;
                sem_init(&sem_terrain, 0, 1);

                /*On lance un thread par personne */
                for (int i = 0; i < t.liste_personnes.size(); ++i)
                {

                    //Mise en place contexte
                    sem_t s_private;
                    sem_init(&s_private, 0, 0);
                    v_private.push_back(&s_private);
                    Contexte my_contexte(2,&t,&sem_terrain,&s_private,&(t.liste_personnes[i]));
                    cout<<my_contexte._etape<<endl;

                    //lancement thread
                    pthread_t th_personne;
                    pthread_create(&th_personne, NULL, thread_avancerALONE, &my_contexte);

                    cout<<"je lance un thread"<<endl;

                    
                }

                /*On attend la fin de chaque thread */
                for (sem_t* s_private: v_private)
                {
                    sem_wait(s_private);
                    cout<<"liberez private"<<endl;

                    sem_destroy(s_private);
                }
                //PB DANS LA MANIERE DATTENDRE

                sem_destroy(&sem_terrain);
            }

        }   
    

    tempsFin = clock();
    end = time(NULL);
    if (time_execution)
    {
        printf("Temps processeur utilisé: %.3lf secondes\n", (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC);
        getrusage(RUSAGE_SELF,&r_usage);
        utime = r_usage.ru_utime;
        stime = r_usage.ru_stime;
        printf("RUSAGE:\n");
        printf("\tEmpreinte maximale du programme: %ld\n",r_usage.ru_maxrss);
        printf("\tTemps CPU : \n\t\tTemps système utilisateur utilisé (ru_utime): %ld.%06ld \n\t\tTemps sytème  utilisé(ru_stime):  %ld.%06ld \n",
        (int64_t)utime.tv_sec, (int64_t)utime.tv_usec,
        (int64_t)stime.tv_sec, (int64_t)stime.tv_usec);
    }
    return 0;

}