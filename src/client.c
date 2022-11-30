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

    color map[HEIGHT][WIDTH];
    readMap(map);
    printMap(map);

    return 0;
}