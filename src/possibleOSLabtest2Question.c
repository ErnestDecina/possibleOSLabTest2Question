//
// possibleOSLabtestQuestion2.c
// Desc: Possible Operating System LabTest2 Question
//     
// Author: Ernest John Decina 
// Date: 9th of December 2022
//

// Libraries
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// Symbolic Names
#define SIZE 12


// Global Variables
int buffer[SIZE];
// sem_t mutex;
pthread_mutex_t mutex;
pthread_mutex_t mutex_consumer;
sem_t number_empty_slots;
sem_t number_full_slots;

// Structures

// Function Prototypes
void *addValueBuffer(void *);
void *removeValueBuffer(void *);
void printBuffer(void);

// Main Driver
int main(void)
{
    // Variables
    pthread_t producer_thread_id[SIZE];
    pthread_t consumer_thread_id[SIZE];

    // Initialize Semaphores
    // sem_init(&mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_consumer, NULL);
    sem_init(&number_empty_slots, 0, SIZE);
    sem_init(&number_full_slots, 0, 0);

    // pthread_mutex_lock(&mutex_consumer);

    // Create Producer Thread
    for(int i = 0; i < SIZE; i++)
    {
        pthread_create(&producer_thread_id[i], NULL, addValueBuffer, NULL);
    } // End for

    pthread_mutex_unlock(&mutex_consumer);

    // Create Producer Thread
    for(int i = 0; i < SIZE; i++)
    {
        pthread_create(&consumer_thread_id[i], NULL, removeValueBuffer, NULL);
    } // End for


    for(int i = 0; i < SIZE; i++)
    {
        pthread_join(producer_thread_id[i], NULL);
        pthread_join(consumer_thread_id[i], NULL);
    } // End for

    // Remove Semaphores
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_consumer);
    sem_destroy(&number_empty_slots);
    sem_destroy(&number_full_slots);

    return 0;
} // End main

// Function Declarations

//
//  void *addValueBuffer(int)
//  Desc: Adds Value into Buffer
//
void *addValueBuffer(void *args)
{
    // Wait
    pthread_mutex_lock(&mutex);
    sem_wait(&number_empty_slots);

    // Variables
    static int index = 1;
    int number_slots_filled = 0;

    // Get number of slots filled
    sem_getvalue(&number_full_slots, &number_slots_filled);

    // TODO: Implement Adding Value into buffer
    buffer[number_slots_filled] = index;
    index++;

    printf("\nThread %ld adding value: %d", pthread_self(), index);
    printBuffer();

    // Signal
    sem_post(&number_full_slots);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
} // End void *addValueBuffer(int)

//
//  void *removeValueBuffer(void)
//  Desc: Remove values from Buffer
//
void *removeValueBuffer(void *args)
{
    // Wait
    pthread_mutex_lock(&mutex);   
    sem_wait(&number_full_slots);

    // Variables
    int number_slots_empty = 0;

    // Get number of slots filled
    sem_getvalue(&number_empty_slots, &number_slots_empty);


    // TODO: Implement remove value from Buffer
    printf("\nValue Removed: %d at thread: %d", buffer[0], number_slots_empty);

    // Shift Values up
    for(int index_buffer = 0; index_buffer < SIZE - number_slots_empty + 1; index_buffer++)
    {
        buffer[index_buffer] = buffer[index_buffer + 1];
    } // End for

    buffer[SIZE - number_slots_empty] = 0;

    printBuffer();

    // Signal
    sem_post(&number_empty_slots);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
} // End void *removeValueBuffer(int)

//
//  void printBuffer(void)
//  Desc: Prints Buffer
//
void printBuffer(void)
{
     printf("\n");
    for(int i = 0; i < SIZE; i++) 
    {
        if(i == 0)
        {
            printf("Head <- [%d] <- ", buffer[i]);
        } // End if

        else if(i == SIZE - 1)
        {
            printf("[%d] <- Tail", buffer[i]);
        } // End if

        else
        {
            printf("[%d] <- ", buffer[i]);
        }
    } // End for
    
    printf("\n");
} // End void printBuffer(void)