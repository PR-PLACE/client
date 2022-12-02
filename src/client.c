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

    // color map[HEIGHT][WIDTH];
    // readMap(map);
    // printMap(map);

    pixel_t pixel = enterPixel();
    printf("pixel entered : x = %d, y = %d\n", pixel.abscissa, pixel.ordinate);
    // infoShm();
    removeClient();
    // infoShm();
    printf("shmid = %d\n", shmid);
    return 0;
}