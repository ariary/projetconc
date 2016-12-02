#ifndef MONITEUR_H
#define MONITEUR_H
#include <pthread.h>
#include <atomic>


class Moniteur
{
	public:
		std::atomic<int> NEavailable;
		std::atomic<int> NOavailable;
		std::atomic<int> SEavailable;
		std::atomic<int> SOavailable;

		pthread_cond_t* cond; //tableau de condition
		pthread_mutex_t mutex;

		Moniteur(pthread_cond_t* cond,pthread_mutex_t& mutex);
};

#endif