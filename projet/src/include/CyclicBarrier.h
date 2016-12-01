#ifndef CYCLIC_H
#define CYCLIC_H
#include <semaphore.h> //utilisation sémarphore
 #include <unistd.h>
#include <atomic>
#include "CyclicBarrier.h"

class CyclicBarrier
{
public:
	std::atomic<int> nb_expected;
	sem_t join;
	CyclicBarrier(int i);
	void await();
	void block();
};
#endif