#include <sys/shm.h>

#define PROJECT_ID 10

#define KEY_FILE_NAME "key_file"

#define SHM_FLAG 0666 | IPC_CREAT | IPC_EXCL