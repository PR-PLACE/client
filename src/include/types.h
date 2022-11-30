#ifndef INCLUDED_TYPES
#define INCLUDED_TYPES 1

#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PROJECT_ID 12

#define KEY_FILE_NAME "pr-place-shm"

#define SHM_FLAG 0666

#define COLUMNS_NUMBER 50
#define ROWS_NUMBER 50

#define SHARED_MEMORY_FILE "../pr-place-shm"

#define SEMAPHORE_NAME "/PR_PLACE"
#define SEMAPHORE_PERMISSIONS 0666

typedef struct client_list_t
{
    int nb_client;
    pid_t *client_list;
} client_list_t;

#define CHECK(sts, msg) \
    if ((sts) == -1)    \
    {                   \
        perror(msg);    \
        exit(-1);       \
    }

#endif