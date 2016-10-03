#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> //atoi
#include "include/terrain.h"
#include "include/mythreads.h"
#include  <iostream>
#include <getopt.h>
#include <sys/resource.h> //getrusage
#include <SFML/Graphics.hpp>
#include <math.h> //pow
#include <pthread.h>


using namespace std;
int main(int argc, char *argv[]){
    
    
    /*-m*/
    /*struct rusage r_usage;
    clock_t tempsDebut, tempsFin;
    struct timeval utime;
    struct timeval stime;
    time_t begin,end;
    

    /*prise en charge des arguments*/
    /*int nb_personne,nb_thread;
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
    begin= time(NULL);



    /*lancement du programme*/
    terrain t = terrain((int)pow(2,0)) ;//terrain t = terrain((int)pow(2,nb_personne)) ;

    cout << "il y a " << t.liste_personnes.size() << "personnes" << endl;
    t.print_liste_personnes(); 

    for(int i = 0; i < t.liste_personnes.size(); i++){
            cout << "first ";
            t.liste_personnes.at(i).print_personne();
            t.avancer(t.liste_personnes.at(i));
            cout << "second ";
            t.liste_personnes.at(i).print_personne();
    }

    /*if (nb_thread==0)
    {
        pthread_t t0;
        pthread_create(&t0, NULL, thread_avancerALL, &t);
        pthread_join(t0, NULL);
        
    }else if(nb_thread==1){
        pthread_t t1; //NE
        pthread_t t2; //NO
        pthread_t t3; //SE
        pthread_t t4; //SO

        pthread_create(&t1, NULL, thread_avancerNE, &t);
        pthread_create(&t2, NULL, thread_avancerNO, &t);
        pthread_create(&t3, NULL, thread_avancerSE, &t);
        pthread_create(&t4, NULL, thread_avancerSO, &t);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
        pthread_join(t4, NULL);

    }else{//nb_thread=4

        Data d; // pour passer en paramètre du thread et le terrain et l'indice de la personne à gérer
        d.t=t;
        
        vector<pthread_t> v_thread; //création pour l'attente des threads
        
        /*On lance un thread par personne */
        /*for (int i = 0; i < t.liste_personnes.size(); ++i)
        {
            pthread_t th_personne;
            d.indice_personne=i;
            pthread_create(&th_personne, NULL, thread_avancerALONE, &d);
            v_thread.push_back(th_personne);
        }

        /*On attend la fin de chaque thread */
        /*for (pthread_t t : v_thread)
        {
            pthread_join(t, NULL);
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
    }*/
    return 0;

}