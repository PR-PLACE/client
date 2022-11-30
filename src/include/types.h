#ifndef INCLUDED_TYPES
#define INCLUDED_TYPES 1

#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PROJECT_ID 20

#define KEY_FILE_NAME "pr-place.shm"

#define SHM_FLAG 0666 | IPC_CREAT

#define NB_CLIENT_MAX 100

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