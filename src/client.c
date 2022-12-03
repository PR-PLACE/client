#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "include/libclient.h"
#include "include/libmap.h"
#include "include/types.h"

extern int shmid;
extern pthread_mutex_t mutex_timer;

int main(int argc, char **argv)
{
    loadShm();
    addClient();

    drawMap();
    pthread_t thread_timer = createTimer();

    while (1)
    {
        pthread_mutex_lock(&mutex_timer);
        pixel_t pixel = enterPixel();
        placePixel(pixel);
        pthread_mutex_unlock(&mutex_timer);
        sleep(1); // let the thread timer the time to take the mutex
    }

    // infoShm();
    removeClient();
    // infoShm();
    printf("shmid = %d\n", shmid);

    pthread_join(thread_timer, NULL);
    return 0;
}