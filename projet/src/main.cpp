#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "include/terrain.h"
#include "include/mythreads.h"
#include  <iostream>
#include <getopt.h>
#include <sys/resource.h> //getrusage
//#include <SFML/Graphics.hpp>
#include <math.h> //pow
#include <pthread.h>


using namespace std;
int main(int argc, char *argv[]){
    
    
    /*-m*/
    struct rusage r_usage;
    clock_t tempsDebut, tempsFin;
    struct timeval utime;
    struct timeval stime;
    

    /*prise en charge des arguments*/
    int nb_personne,nb_thread;
    bool time_execution=false;
    int opt;
    while ((opt = getopt(argc , argv, "mp:t:")) != -1){
        switch (opt) {
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

    printf("nb de personne 2^%d; nb de threads %d; ", nb_personne, nb_thread);
    (time_execution)?printf("Avec mesure de temps\n\n"):printf("sans mesure de temps\n\n");
    tempsDebut = clock();



    /*lancement du programme*/
    terrain t = terrain((int)pow(2,0)) ;//terrain t = terrain((int)pow(2,nb_personne)) ;
    t.initialiser_matrice();
    t.print_liste_personnes(); 

    if (nb_thread==0)
    {
        pthread_t t0;
        pthread_create(&t0, NULL, thread_avancerALL, NULL);
        pthread_join(t0, NULL);
    }else if(nb_thread==1){
        int j=0;
    }else{//nb_thread=4
        int k=0;
    }
    

    tempsFin = clock();
    if (time_execution)
    {
        printf("Temps processeur utilisé: %.3lf secondes\n", (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC);
        getrusage(RUSAGE_SELF,&r_usage);
        utime = r_usage.ru_utime;
        stime = r_usage.ru_stime;
        printf("RUSAGE:\n");
        printf("\tEmpreinte maximale du programme: %ld\n",r_usage.ru_maxrss);
        printf("\tTemps CPU : \n\t\tTemps système utilisé (ru_utime): %ld.%06ld \n\t\tTemps sytème utilisateur utilisé(ru_stime):  %ld.%06ld \n",
        (int64_t)utime.tv_sec, (int64_t)utime.tv_usec,
        (int64_t)stime.tv_sec, (int64_t)stime.tv_usec);
    }
    
    return 0;

}