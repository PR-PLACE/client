#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "include/libclient.h"
#include "include/types.h"

extern int shmid;

int main(int argc, char **argv)
{
    loadShm();
    infoShm();
    addClient();
    infoShm();
    removeClient();
    infoShm();
    printf("shmid = %d\n", shmid);
    return 0;
}