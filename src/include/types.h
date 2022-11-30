#ifndef INCLUDED_TYPES
#define INCLUDED_TYPES 1

#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define NB_CLIENT_MAX 100
#define PROJECT_ID 12
#define SHM_FLAG 0666 | IPC_CREAT
#define SHARED_MEMORY_FILE "../pr-place.shm"

#define SEMAPHORE_NAME "/PR_PLACE"
#define SEMAPHORE_PERMISSIONS 0666

typedef struct client_list_t
{
    int nb_client;
    pid_t client_list[NB_CLIENT_MAX];
} client_list_t;

#define CHECK(sts, msg) \
    if ((sts) == -1)    \
    {                   \
        perror(msg);    \
        exit(-1);       \
    }

#endif