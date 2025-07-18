/*
    Authors: Jose Urrea, ......
    Class Account Username: cssc1465, .....
    Class Informartion: CS 480, Summer 2025
    Assignment Information : Programming Assignment #1
    File : bots.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "bots.h"

sem_t FLAG; // Semaphore to manage access to the files


void *thread_function(void *arg) {
    int thread_num = *((int*)arg);  // Cast pointer to recognize int
    pthread_t tid = pthread_self();  // thread id

    // Even and odd quotes
    const char *even_quote = "Controlling complexity is the essence of computer programming. --Brian Kernighan\n";
    const char *odd_quote  = "Computer science is no more about computers than astronomy is about telescopes. --Edsger Dijkstra\n";

    int delay = (thread_num % 2 == 0) ? 2 : 3;    // Delay of thread 2 for even, 3 for odd
    const char *quote = (thread_num % 2 == 0) ? even_quote : odd_quote;  // quote = even or odd depending on thread number

    // Initiate thread to run 8 times
    for (int i = 0; i < 8; i++) {
        sleep(delay);  // Call delay 

        sem_wait(&FLAG); // Initiate semaphore

        // Open QUOTE.txt file and appen thread id along with quote
        FILE *file = fopen("QUOTE.txt", "a");
        if (file) {
            fprintf(file, "Thread %d: %s", tid, quote);
            fclose(file);
        } else {
            perror("QUOTE.txt could not be open");
        }
        
        // Output to console thread id
        printf("Thread %lu is running\n", (unsigned long)tid);

        sem_post(&FLAG); // Release semaphore
    }

    pthread_exit(NULL);
}
