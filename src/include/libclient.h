
#include "libmap.h"
#ifndef INCLUDE_LIB
#define INCLUDE_LIB 1

/**
 * Function to set up the signal handler in order to catch :
 * - SIGUSR1 => signal to read the map
 * - SIGTERM/SIGHUP/SIGINT => signal to remove the client from the shared memory before terminating the process
 */
void setupSignalHandler();

/**
 * Function to initialize the map variable
 */
void setupMap();

/**
 * Function to create the thread concerning the timer.
 * After each sequence of timer, it waits the condition given by the user after placing a pixel.
 */
void setupThread();

/**
 * Function to create the tread used to place a pixel
 */
void createThreadPixel();

/**
 * Function waiting the thread  of placing pixel to be terminated
 */
void waitForThreadPixel();

/**
 * Function responsible to allow the user placing a pixel in the map.
 * After placing the pixel, we valid the condition for the timer to restart.
 * We send a SIGUSR1 to each user in the game to tell them to read the map
 */
void placePixelSequence();

/**
 * Routine of  the thread responsible to place a pixel. That thread is deleted after placing a pixel.
 */
void *placePixelThread(void *arg);

/**
 * Handler of the signals (SIGUSR1, SIGINT, SIGTERM, SIGUP)
 * @param int sig_number : nnumber of the signal
 */
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

#endif