/*
    Authors: Jose Urrea, Abdihakim Ahmed
    Class Account Username: cssc1465, cssc1402
    Class Informartion: CS 480, Summer 2025
    Assignment Information : Programming Assignment #1
    File : bots.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
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

        sem_wait(&FLAG); // Initiate wait semaphore

        // Open QUOTE.txt file and appen thread id along with quote
        FILE *file = fopen("QUOTE.txt", "a");
        if (file) {
            fprintf(file, "Thread %lu: %s", (unsigned long)tid, quote);
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
// Funtction to run threads
void run_threads(void) {
    pthread_t threads[7];  // array of threads
    int thread_ids[7];     // array of thread ids

    // Create QUOTE.txt 
    FILE *file = fopen("QUOTE.txt", "w");
    if (!file) {
        perror("Error at creating QUOTE.txt");
        exit(EXIT_FAILURE);
    }
    // Print thread id and close file
    fprintf(file, "%lu\r\n",(unsigned long) getpid());
    fclose(file);

    // Initialize semaphore
    if (sem_init(&FLAG, 0, 1) != 0) {
        perror("Error at initializing semaphore");
        exit(EXIT_FAILURE);
    }

    // Create threads to perform threa_function
    for (int i = 0; i < 7; i++) {
        thread_ids[i] = i;
        pthread_t new_thread = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (new_thread != 0) {
            perror("Could not create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads
    for (int i = 0; i < 7; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up semaphore
    sem_destroy(&FLAG);

    printf("Thread process completed\n");
}

