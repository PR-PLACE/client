#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
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

    // Initialize the shared memory

    key_t token = ftok("../pr-place-map", PROJECT_ID);
    if (token == -1)
    {
        perror("ftok");
        return 1;
    }
    printf("Token created %d\n", token);

    printf("Creating the shared memory segment\n");
    int shmid = shmget(token, sizeof(client_list_t), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }
    printf("Shared memory segment created with id %d\n", shmid);

    return 0;
}
