#ifndef INCLUDE_LIB
#define INCLUDE_LIB 1

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

#endif