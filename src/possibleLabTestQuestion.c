// Library
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
#define TRUE 1
#define FALSE 0

// Structures


// Function Prototypes
bool checkBounderBufferEmpty(int *);
bool checkBounderBufferFull(int *);
void addValueBounderBuffer(int *, int **, int);
void deleteValueBounderBuffer(int *, int **);
void printBounderBuffer(int *);

// Driver Code
int main(int argc, char **argv)
{
    // Variables
    int bounderBuffer[SIZE] = { 0 }; 
    int *ptrTailBounderBuffer = NULL;


    return 0;
} // End main

// Function Declaration
//
// bool checkBounderBufferEmpty(int *bounderBuffer)
// Description: Returns true if BounderBuffer is Empty or false if BounderBuffer isnt empty
//
bool checkBounderBufferEmpty(int *bufferBounder)
{ 
    // Variables
    unsigned int counterISEmpty = 0;

    for(int indexBounderBuffer = 0; indexBounderBuffer < SIZE; indexBounderBuffer++)
    {
        // Check if there is a non NULL value in BufferBounder therefore not empty
        if(*(bufferBounder + indexBounderBuffer) == 0 )
            counterISEmpty++;    
    } // End for

    if(counterISEmpty == SIZE) return true;
    else return false;
} // End void checkBounderBufferEmpty(int bounderBuffer[])

//
// bool checkBounderBufferFull(int *bounderBuffer)
// Description: Returns true if BounderBuffer is Full or false if BounderBuffer isnt full
//
bool checkBounderBufferFull(int *bufferBounder)
{
    // Varaibles
    unsigned int counterNotEmpty = 0;

    for(int indexBounderBuffer = 0; indexBounderBuffer < SIZE; indexBounderBuffer++)
    {
        // Check if there is a non NULL value in BufferBounder therefore not empty
        if(*(bufferBounder + indexBounderBuffer) != 0 )
            counterNotEmpty++;    
    } // End for


    if(counterNotEmpty == SIZE) return true;
    else return false;
} // End bool checkBounderBufferFull(int *ptrTailBounderBuffer, int *ptrHeadBounderBuffer)

//
// bool addValueBounderBuffer(int *bounderBuffer, int value)
// Description: Adds Value to buffer
//
void addValueBounderBuffer(int *ptrHeadBounderBuffer, int **ptrTailBounderBuffer, int value)
{
    // Exit if bounderBuffer is Full
    if(checkBounderBufferFull(ptrHeadBounderBuffer))
    {
        printf("\n\nBounderBuffer full cannot add item: %d", value);
        printf("\nExiting...");
        return;
    } // End if

    // Check if bounderBuffer is Empty
    if(checkBounderBufferEmpty(ptrHeadBounderBuffer))
    {
        printf("\n\nStarting BounderBuffer with value %d", value);

        // Set tail to Head
        *ptrTailBounderBuffer = ptrHeadBounderBuffer;

        // Add Value into Buffer
        **ptrTailBounderBuffer = value;

        return;
    } // End if

    // Set ptrTailBounderBuffer to next spot
    *ptrTailBounderBuffer = *ptrTailBounderBuffer + 1;

    // Add Value into Buffer
    **ptrTailBounderBuffer = value;

} // End void addValueBounderBuffer(int *, int);

//
// void deleteValueBounderBuffer(int *, int **, int);
// Description: Removes Value to buffer
//
void deleteValueBounderBuffer(int *ptrHeadBounderBuffer, int **ptrTailBounderBuffer)
{
    // Check if bounderBuffer is Empty
    if(checkBounderBufferEmpty(ptrHeadBounderBuffer))
    {
        printf("\nCannot Remove Value since BounderBuffer is Empty\n");
        return;
    } // End if

    // Shift Items up the array
    for(int indexBounderBuffer = 0; indexBounderBuffer < ((*ptrTailBounderBuffer - ptrHeadBounderBuffer) + 1); indexBounderBuffer++)
    {
        // Check for last value
        if(indexBounderBuffer == ((*ptrTailBounderBuffer - ptrHeadBounderBuffer)))
        {
            // Change ptrTailBounderBuffer
            *ptrTailBounderBuffer = *ptrTailBounderBuffer - 1;

            // Set last value to 0
            *(ptrHeadBounderBuffer + indexBounderBuffer) = 0;
            return;
        } // End if

        // Shift values up
        *(ptrHeadBounderBuffer + indexBounderBuffer) = *(ptrHeadBounderBuffer + indexBounderBuffer + 1);

    } // End for
} // End void deleteValueBounderBuffer(int *, int **, int)

//
// void printBounderBuffer(int *bounderBuffer)
// Description: Prints BounderBuffer
//
void printBounderBuffer(int *bounderBuffer)
{
    printf("\n\n");
    for(int i = 0; i < SIZE; i++) 
    {
        if(i == 0)
        {
            printf("Head <- [%d] <- ", bounderBuffer[i]);
        } // End if

        else if(i == SIZE - 1)
        {
            printf("[%d] <- Tail", bounderBuffer[i]);
        } // End if

        else
        {
            printf("[%d] <- ", bounderBuffer[i]);
        }
    } // End for
    
    printf("\n");
} // End void printBounderBuffer(int *);