#ifndef MONITEUR_H
#define MONITEUR_H
#include <pthread.h>
#include <atomic>
#include <utility>

using namespace std;
class Moniteur
{
	public:
		//t1
		pair <pthread_mutex_t,pthread_cond_t> pr_zone1;
		pair <pthread_mutex_t,pthread_cond_t> pr_zone2;
		pair <pthread_mutex_t,pthread_cond_t> pr_zone3;
		pair <pthread_mutex_t,pthread_cond_t> pr_zone4;

		std::atomic<int> available1;
		std::atomic<int> available2;
		std::atomic<int> available3;
		std::atomic<int> available4;

		Moniteur(); //pour t1

		//t2
		std::atomic<int> available;

		pthread_cond_t* cond; //tableau de condition ou ptr de condition
		pthread_mutex_t mutex;

		Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex); //pour t2
};

#endif