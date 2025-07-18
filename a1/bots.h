#ifndef BOTS_H
#define BOTS_H

#include <pthread.h>
#include <semaphore.h>

extern sem_t FLAG;

void thread_function();

void run_threads();

#endif
