#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "include/libclient.h"
#include "include/libmap.h"
#include "include/types.h"

extern int shmid;

int main(int argc, char **argv)
{
    loadShm();
    addClient();
    setupSignalHandler();
    printf("My pid is %d\n", getpid());
    // placePixel(15, 15, ROUGE);
    drawMap();
    while (1)
    {
        placePixelSequence();
    }
    return 0;
}