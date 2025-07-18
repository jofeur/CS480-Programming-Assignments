#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 7  // Number of threads

sem_t FLAG; // Semaphore for synchronization
FILE *file;  // File pointer for QUOTE.txt

// Define your custom quotes here
const char *quote1 = "Your first custom quote here!";
const char *quote2 = "Your second custom quote here!";

// Function to write quotes to the shared file
void* bot_thread(void *thread_id) {
    long tid = (long) thread_id;  // Thread ID
    const char *quote_to_write = (tid % 2 == 0) ? quote1 : quote2;  // Assign quote based on thread ID

    int sleep_time = (tid % 2 == 0) ? 2 : 3;  // Even threads sleep 2 seconds, odd threads 3 seconds

    // Periodically get the semaphore and write to the file
    for (int i = 0; i < 7; i++) {
        sem_wait(&FLAG);  // Wait for the semaphore to be available

        // Open the QUOTE.txt file in append mode and write the quote
        file = fopen("QUOTE.txt", "a");
        if (file == NULL) {
            perror("Unable to open QUOTE.txt");
            exit(1);
        }
        
        fprintf(file, "Thread ID %ld: \"%s\"\n", tid, quote_to_write);
        fclose(file);

        // Print to the console
        printf("Thread %ld is running\n", tid);

        sem_post(&FLAG);  // Release the semaphore

        // Sleep for the specified time
        sleep(sleep_time);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];  // Array to hold thread IDs
    long t;

    // Step 1: Create and open the QUOTE.txt file and write the PID
    FILE *init_file = fopen("QUOTE.txt", "w");
    if (init_file == NULL) {
        perror("Unable to create QUOTE.txt");
        exit(1);
    }
    
    // Write the process ID to the file
    fprintf(init_file, "Process ID: %d\n", getpid());
    fclose(init_file);

    // Step 2: Initialize the semaphore with a value of 1 (binary semaphore)
    sem_init(&FLAG, 0, 1);

    // Step 3: Create 7 threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread, in main(): %ld\n", t + 1);
        pthread_create(&threads[t], NULL, bot_thread, (void*) t + 1);  // Thread creation
    }

    // Step 4: Block and wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);  // Wait for threads to complete
    }

    // Step 5: Destroy the semaphore and exit gracefully
    sem_destroy(&FLAG);
    printf("All threads have completed their work. Exiting...\n");

    return 0;
}

