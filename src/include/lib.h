#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PROJECT_ID 10

#define KEY_FILE_NAME "pr-place-shm"

#define SHM_FLAG 0666 | IPC_CREAT | IPC_EXCL

#define COLUMNS_NUMBER 50
#define ROWS_NUMBER 50

#define MAP_FILENAME "pr-place-map"

typedef struct client_list_t
{
    int nb_client;
    pid_t *client_list;
} client_list_t;
