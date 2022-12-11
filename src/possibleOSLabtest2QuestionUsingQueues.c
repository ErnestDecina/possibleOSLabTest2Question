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

// sem_t mutex;
pthread_mutex_t mutex;
sem_t number_empty_slots;
sem_t number_full_slots;

// Structures
typedef struct node {
    int value;
    struct node *next_node;
    struct node *previous_node;
} node;

// Function Prototypes
void *addValueBuffer(void *);
void *removeValueBuffer(void *);
void printBuffer(void);


// Global Variables
node *ptr_head_buffer = NULL;
node *ptr_tail_buffer = NULL;


// Main Driver
int main(void)
{
    // Variables
    node *buffer = (node *)malloc(sizeof(node));
    ptr_head_buffer = buffer;

    pthread_t producer_thread_id[SIZE];
    pthread_t consumer_thread_id[SIZE];

    // Initialize Semaphores  
    pthread_mutex_init(&mutex, NULL);
    sem_init(&number_empty_slots, 0, SIZE);
    sem_init(&number_full_slots, 0, 0);


    // Create Producer Thread
    for(int i = 0; i < SIZE; i++)
        pthread_create(&producer_thread_id[i], NULL, addValueBuffer, NULL);
    // End for


    // Make Sure Produce Thread Finishes
    for(int i = 0; i < SIZE; i++)
        pthread_join(producer_thread_id[i], NULL);
    // End for


    // Create Consumer Thread
    for(int i = 0; i < SIZE; i++)
        pthread_create(&consumer_thread_id[i], NULL, removeValueBuffer, NULL);
    // End for


    // Make Sure Consumer Thread Finishes
    for(int i = 0; i < SIZE; i++)
        pthread_join(consumer_thread_id[i], NULL);
    // End for
    

    // Remove Semaphores
    pthread_mutex_destroy(&mutex);
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

    node *node = malloc(sizeof(node));
    node->value = index;

    // Start of Queue
    if(ptr_tail_buffer == NULL)
    {
        ptr_head_buffer = node;
        ptr_tail_buffer = node;
        node->next_node = NULL;
        node->previous_node = NULL;

        printBuffer();

        sem_post(&number_full_slots);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);

        return NULL;
    } // End if

    // Add to end of queue
    ptr_tail_buffer->previous_node = node;
    node->next_node = ptr_tail_buffer;
    node->previous_node = NULL;
    ptr_tail_buffer = node;

    printf("\nAdding value: %d", index);
    printBuffer();

    index++;

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
    node *node = ptr_head_buffer;
    

    // Dequeue Value
    if(ptr_head_buffer->previous_node == NULL)
    {
        free(node);
        ptr_head_buffer = NULL;

        sem_post(&number_empty_slots);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);

        return NULL;
    } // End if

    ptr_head_buffer = node->previous_node;
    ptr_head_buffer->next_node = NULL;

    free(node);

    printf("\nValue Removed: %d", ptr_head_buffer->value);
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
    // Variables
    node *node = ptr_tail_buffer;

    printf("\n");
    
    while (node->next_node != NULL) 
    {
        // Print Tails
        if(node == ptr_tail_buffer)
            printf("Tail -> [%d] -> ", node->value);    
        else 
            printf("[%d] -> ", node->value);
        
        node = node->next_node;
    } // End for

    printf("Head");
    printf("\n");
} // End void printBuffer(void)