
#include <pthread.h>
#include "libmap.h"
#ifndef INCLUDE_LIB
#define INCLUDE_LIB 1
void placePixelSequence();
void setupSignalHandler();
void handler(int sig_number);

/**
 * Function to load the shared memory
 */
void loadShm();

/**
 * Function to show shared memory information
 */
void infoShm();

/**
 * Function to add the current process as a client in the shared memory
 */
void addClient();

/**
 * Function removing the client from the shared memory
 */
void removeClient();

/**
 * Function to ask the user to enter the pixel he wants to add. If the coordinates of the pixlel returned are -1,-1 then esc was pressed
 * @returns pixel_t  : the pixel he wants to add
 */
pixel_t enterPixel();

/**
 * Function to read a number from stdin
 * @returns int : number entered or -1 if pressed esc
 */
int readNumber();

/**
 * Function to test the pixel entered by the client
 * @param pixel_t** pixel : the pixel the user wants to add
 */
void _testPixelCoord(pixel_t **pixel);

/**
 * Function creating the timer and the thread associated
 * @returns pthread_t : the thread created
 */
pthread_t createTimer();

/**
 * Routine of the timer thread
 * @param void* arg : the time the user has to wait before putting a pixel
 */
void *_threadTimer(void *arg);
#endif