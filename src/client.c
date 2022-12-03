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
    setupThread();
    setupMap();
    for (;;)
    {   
        createThreadPixel();
        waitForThreadPixel();
        
    }

    return 0;
}