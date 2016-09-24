#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "./include/personne.h"
#include "./include/terrain.h"
#include  <iostream>
#include <getopt.h>



int main(int argc, char *argv[]){
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
    (time_execution)?printf("Avec mesure de temps \n"):printf("sans mesure de temps\n");
    


    //(time_execution)?printf("Avec mesure de temps \n"):printf("sans mesure de temps\n");


    /*lancement du programme*/
    //init(int nb_personne,nb_thread,bool time_execution)

    //app

    
    return 0;
}