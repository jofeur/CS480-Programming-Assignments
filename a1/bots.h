/*
    Authors: Jose Urrea, Abdihakim Ahmed
    Class Account Username: cssc1465, cssc1402
    Class Informartion: CS 480, Summer 2025
    Assignment Information : Programming Assignment #1
    File : bots.h
*/

#ifndef BOTS_H
#define BOTS_H

#include <pthread.h>
#include <semaphore.h>

extern sem_t FLAG;

void thread_function();

void run_threads();

#endif
