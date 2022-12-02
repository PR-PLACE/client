#include "include/libclient.h"
#include "include/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include "include/libmap.h"

key_t key;
int shmid;

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
    printf("coucou\n");
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

    printf("------Enter a pixel------\n");
    printf("Abscissa : ");
    pixel->abscissa = readNumber();
    if (pixel->abscissa == -1)
    {
        pixel->ordinate = -1;
        return *pixel;
    }

    printf("Ordinate : ");
    pixel->ordinate = readNumber();
    if (pixel->ordinate == -1)
    {
        pixel->abscissa = -1;
        return *pixel;
    }

    _testPixelCoord(&pixel);

    printf("Choose a color from : ");
    for (char i = 0; i < COLOR_NUMBER; i++)
    {
        printf("%d-", colors[i]);
        printColoredChar(colors[i]);
        printf(" ");
    }
    printf("\nColor chosen : ");
    scanf("%d", &choice);
    pixel->color = (color)choice;
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
    char carac = ' ';
    char string_length = 1;
    char *number_as_string = (char *)malloc(sizeof(char));
    *number_as_string = '\0';
    while (carac != 27 && carac != '\n')
    {
        carac = getchar();
        string_length++;
        number_as_string = realloc(number_as_string, string_length * sizeof(char));
        number_as_string[string_length - 2] = carac;
        number_as_string[string_length - 1] = '\0';
    }
    fflush(stdin);
    if (carac == 27)
        return -1;
    else
        return atoi(number_as_string);
}