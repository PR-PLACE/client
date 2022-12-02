#include "include/libclient.h"
#include "include/libmap.h"
#include "include/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

key_t key;
int shmid;

void placePixelSequence()
{
    pixel_t *pixel = (pixel_t *)malloc(sizeof(pixel_t));
    color newColor;
    printf("Enter the column of the pixel to place : ");
    scanf("%d", &(pixel->abscissa));
    printf("Enter the line of the pixel to place : ");
    scanf("%d", &(pixel->ordinate));
    drawMap();
    printf("Enter the color => ");
    for (int i = 0; i < NB_COLORS; i++)
    {
        printf("%d:", i + 1);
        printColoredChar(colors[i]);
        printf(" ");
    }
    printf(" : ");
    scanf("%d", &newColor);
    pixel->color = colors[newColor - 1];
    placePixel(*pixel);
    drawMap();
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
        sleep(4);
        drawMap();
        break;
    case SIGTERM:
    case SIGINT:
        printf("Received SIGINT to exit\n");
        removeClient();
        exit(0);
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------------------------------------

void loadShm()
{
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