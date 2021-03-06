#include "./include/CyclicBarrier.h"
#include <iostream>
#include <semaphore.h>

using namespace std;

CyclicBarrier::CyclicBarrier(int i){
	this->nb_expected=i;
	if(sem_init(&(this->join), 0, 0)) //sémaphore privée
	{
	    perror("sem_init()");
	    exit(1);
	}
}

void CyclicBarrier::await(){
	this->nb_expected--;
	cout<<">> Attente de "<<nb_expected<<" threads à la barrière"<<flush<<endl;
}

void CyclicBarrier::block(){
	while(nb_expected!=0){}
	  if(sem_post(&(this->join))==-1)
	  {
	      perror("sem_post()");
	      exit(1);
	  }
}