/*
 *
 * File: main.cpp
 * Author: Adrien Prestini & Antoine Rabenandrasana
 * 
 * Version: rendu du 10 octobre 2016
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
                
                sem_t sem_terrain;
                sem_init(&sem_terrain, 0, 1);
                Contexte my_contexte(2,&t,&sem_terrain);

                pthread_create(&t1, NULL, thread_avancerNE, &my_contexte);
                pthread_create(&t2, NULL, thread_avancerNO, &my_contexte);
                pthread_create(&t3, NULL, thread_avancerSE, &my_contexte);
                pthread_create(&t4, NULL, thread_avancerSO, &my_contexte);


                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                pthread_join(t3, NULL);
                pthread_join(t4, NULL);

                sem_destroy(&sem_terrain);
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


                sem_t sem_terrain;
                sem_init(&sem_terrain, 0, 1);
                Contexte c(2,&t,&sem_terrain);
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
        //printf("time :%f\n",difftime(end, begin) );
    }
    return 0;

}