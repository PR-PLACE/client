#include "include/libclient.h"
#include "include/libmap.h"
#include "include/types.h"
#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "include/libmap.h"


key_t key;
int shmid;

char isTimerRunning = 0;
char isPlacingPixel = 0;

map_t *map;


pthread_mutex_t mutexForTimer = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexForPixel = PTHREAD_MUTEX_INITIALIZER;

//Create a cond wait
pthread_cond_t condForTimer = PTHREAD_COND_INITIALIZER;
pthread_cond_t condForPixel = PTHREAD_COND_INITIALIZER;
pthread_t threadTimer;
pthread_t threadPixel;

void setupMap(){
    map = (map_t *)malloc(sizeof(map_t));
    readMap(map);

}

// Signal handling

void setupSignalHandler()
{
    struct sigaction newact;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;

    newact.sa_handler = handler;

    CHECK(sigaction(SIGUSR1, &newact, NULL), "Error setting up signal handler for SIGUSR1");
    CHECK(sigaction(SIGINT, &newact, NULL), "Error setting up signal handler for SIGINT");
    CHECK(sigaction(SIGTERM, &newact, NULL), "Error setting up signal handler for SIGTERM");
}

void handler(int sig_number)
{
    switch (sig_number)
    {
    case SIGUSR1:
        printf("Received SIGUSR1 to update the map\n");
        readMap(map);
        if(isTimerRunning == 0 && isPlacingPixel == 0){
            pthread_cancel(threadPixel);
        }
        break;
    case SIGTERM:
    case SIGINT:
        removeClient();
        exit(0);
        break;
    default:
        break;
    }
}


void broadCastUpdate(){
    client_list_t *client_list = (client_list_t *)shmat(shmid, NULL, SHM_FLAG);
    int nb_client = client_list->nb_client;
    printf("nb_client : %d\n", nb_client);
    for (char i = 0; i < nb_client; i++)
    {
        kill(client_list->client_list[i], SIGUSR1);
    }
    shmdt(client_list);
}

//--------------------------------------------------------------------------------------------


void *placePixelThread(void *arg)
{

    drawMap(map);
    placePixelSequence();
    pthread_exit(NULL);
}
void createThreadPixel(){
    isPlacingPixel = 0;
    pthread_create(&threadPixel, NULL, &placePixelThread, NULL);
}

void waitForThreadPixel(){
    pthread_join(threadPixel, NULL);
}


/*
Thread function of cooldown timer after placed pixel
*/
void *cooldownTimer(void *arg)
{
   while (!pthread_cond_wait(&condForTimer, &mutexForTimer))
    {
        isTimerRunning = 1;
        for (int timer = 10; timer > 0; timer--)
        {
            drawMap(map);
            PRINT_TABS(5);
            printf("\033[1;38;5;%dmCooldown: %d\033[0m\n", GREEN, timer);
            sleep(1);
        }
        isTimerRunning = 0;
        pthread_cond_signal(&condForPixel);
    }
}

void setupThread()
{
    CHECK(pthread_create(&threadTimer, NULL, &cooldownTimer, NULL), "Error creating thread");
}

void placePixelSequence()
{
    pixel_t pixel;
    do pixel = enterPixel();
    while (pixel.abscissa == -1 && pixel.ordinate == -1);
    placePixel(&pixel, *map);
    pthread_cond_signal(&condForTimer);
    broadCastUpdate();
    pthread_cond_wait(&condForPixel, &mutexForPixel);
}

void loadShm()
{
    printf("filename : %s\n", SHARED_MEMORY_FILE);
    key = ftok(SHARED_MEMORY_FILE, PROJECT_ID);
    CHECK(key, "error ftok");
    shmid = shmget(key, sizeof(client_list_t), SHM_FLAG);
    CHECK(shmid, "error shmget");
    return;
}

void infoShm()
{
    struct shmid_ds buf;
    CHECK(shmctl(shmid, IPC_STAT, &buf), "error shmtclt");
    printf("-----------------------Shm information---------------\n");
    printf("Shmid : %d\n", shmid);
    printf("Owner : %d \n", buf.shm_perm.uid);
    printf("Owner's group  :%d \n", buf.shm_perm.gid);
    printf("Creator : %d \n", buf.shm_perm.cuid);
    printf("Creator's group : %d \n", buf.shm_perm.cgid);
    printf("Access mode  : %d \n", buf.shm_perm.mode);
    printf("Segment size : %d \n\n", (int)buf.shm_segsz);

    client_list_t *client_list = (client_list_t *)shmat(shmid, NULL, SHM_FLAG);
    printf("Number of clients : %d \n", client_list->nb_client);
    for (char i = 0; i < client_list->nb_client; i++)
    {
        printf("Client : %d\n", client_list->client_list[i]);
    }
    printf("------------------------------------------------------------------\n");

    return;
}

void addClient()
{
    client_list_t *client_list = (client_list_t *)shmat(shmid, NULL, SHM_FLAG);
    client_list->nb_client += 1;
    int nb_client = client_list->nb_client;
    client_list->client_list[nb_client - 1] = getpid();
    shmdt(client_list);
}

void removeClient()
{
    pid_t pid = getpid();
    client_list_t *client_list = (client_list_t *)shmat(shmid, NULL, SHM_FLAG);
    int nb_client = client_list->nb_client;

    for (char i = 0; i < nb_client; i++)
    {
        if (client_list->client_list[i] == pid)
        {
            // shifting of clients
            for (char j = i; j < nb_client; j++)
                client_list->client_list[j] = client_list->client_list[j + 1];
            client_list->nb_client -= 1;
            client_list->client_list[client_list->nb_client] = 0;
            break;
        }
    }
    return;
}

pixel_t enterPixel()
{
    int choice;
    pixel_t *pixel = malloc(sizeof(pixel_t));
    client_list_t *client_list = (client_list_t *)shmat(shmid, NULL, SHM_FLAG);
    int nb_client = client_list->nb_client;
    PRINT_TABS(1);
    printf("\033[1;38;5;%dmPlayers online\033[0m -> %d\n", PURPLE,nb_client);
    PRINT_TABS(4);
    printf("\033[1;38;5;%dm------Enter a pixel------\033[0m\n",ORANGE);
    PRINT_TABS(1);
    PRINTF_COLOR("Column : ", GREEN);
    pixel->abscissa = readNumber();
    if (pixel->abscissa == -1)
    {
        pixel->ordinate = -1;
        return *pixel;
    }
    PRINT_TABS(1);
    PRINTF_COLOR("LINE : ", GREEN);
    pixel->ordinate = readNumber();
    if (pixel->ordinate == -1)
    {
        pixel->abscissa = -1;
        return *pixel;
    }

    _testPixelCoord(&pixel);
    PRINT_TABS(2);
    PRINTF_COLOR("Colors : ", 8);
    for (char i = 0; i < COLOR_NUMBER; i++)
    {
        printf("%d-", i);
        printColoredChar(colors[i]);
        printf(" ");
    }
    printf("\n");
    PRINT_TABS(1);
    printf("Color: ");
    scanf("%d", &choice);
    getchar();
    pixel->color = colors[choice];
    if (!isColor(pixel->color))
    {
        // we set a default value
        pixel->color = ORANGE;
    }
    return *pixel;
}

void _testPixelCoord(pixel_t **pixel)
{
    // Test the ordinate
    if ((*pixel)->ordinate > HEIGHT)
        (*pixel)->ordinate = HEIGHT;
    else if ((*pixel)->ordinate < 1)
        (*pixel)->ordinate = 1;
    // Test the abscissa
    if ((*pixel)->abscissa > WIDTH)
        (*pixel)->abscissa = WIDTH;
    else if ((*pixel)->abscissa < 1)
        (*pixel)->abscissa = 1;
    return;
}

int readNumber()
{
    char number1;
    char number2;    

    number1 = getchar();
    isPlacingPixel = 1;
    if(number1 == 27){
        getchar();
        return -1;
    }       
    else{
        number2 = getchar();
        if(number2 == 27)
            return -1;
        else if(number2 == '\n')
            return number1 - '0';
        else{
            getchar();
            int number = (number1 - '0') * 10 + (number2 - '0');
            return number;
        }
    }
}