#ifndef INCLUDE_LIBCLIENT
#define INCLUDE_LIBCLIENT 1

#include "libmap.h"

/**
 * Fonction permettant de charger la mémoire partagée
 */
void loadShm();

/**
 * Fonction permettant d'afficher les informations de la mémoire partagée
 */
void infoShm();

/**
 * Fonction pour ajouter un client dans la mémoire partagée
 */
void addClient();

/**
 * Fonction quittant le client de la mémoire partagée
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