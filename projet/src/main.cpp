#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "include/terrain.h"
#include  <iostream>
#include <getopt.h>
#include <sys/resource.h> //getrusage
#include <SFML/Graphics.hpp>


using namespace std;
int main(int argc, char *argv[]){
    
    
    /*prise en charge des arguments*/
    /*int nb_personne,nb_thread;
    bool time_execution=false;
    int opt;

    struct rusage r_usage;//-m
    clock_t tempsDebut, tempsFin;//-m

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
    (time_execution)?printf("Avec mesure de temps \n"):printf("sans mesure de temps\n");
    
*/

    //(time_execution)?printf("Avec mesure de temps \n"):printf("sans mesure de temps\n");
    //tempsDebut = clock();



    /*lancement du programme*/
    //init(int nb_personne,nb_thread,bool time_execution)

    //app

    //tempsFin = clock();
    /*if (time_execution)
    {
        printf("Temps processeur utilisé: %.3lf secondes", (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC)
        getrusage(RUSAGE_SELF,&r_usage);
        printf("Empreinte maximale du programme principal: %ld\n temps utilisateur: %ld.%06ld \n temps système: %ld.%06ld \n",r_usage.ru_maxrss,r_usage.ru_utime.maxrss,r_usage.ru_utime.tv_sec, r_usage.ru_stime.tv_usec);
                getrusage(RUSAGE_CHILDREN,&r_usage);
        printf("Empreinte maximale des threads: %ld\n temps utilisateur: %ld.%06ld \n temps système: %ld.%06ld \n",r_usage.ru_maxrss,r_usage.ru_utime.maxrss,r_usage.ru_utime.tv_sec, r_usage.ru_stime.tv_usec);
    }*/
    terrain t = terrain(100) ;
    t.initialiser_matrice();
    int x = 1;
    while(x > 0){
        
    }
    return 0;

}