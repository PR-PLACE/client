#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../src/include/types.h"
#include "../src/include/libmap.h"

int main(int argc, char const *argv[])
{

    // Initialize the map
    color map[HEIGHT][WIDTH];
    for (int i = 0; i <= HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map[j][i] = BLANC;
        }
    }
    exportMap(map);

    // Initialize the named semaphore
    sem_open(SEMAPHORE_NAME, O_CREAT, SEMAPHORE_PERMISSIONS, 1);

    return 0;
}
