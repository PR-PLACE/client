#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./include/libmap.h"

#define printColoredChar(color) (printf("\033[38;5;%dm██\033[0m", color))

void printLine(color pixels[WIDTH], int lineNumber)
{
    printf("\033[1;38;5;8m %d", lineNumber);
    if (lineNumber < 10)
        printf(" ");
    for (int i = 0; i < WIDTH; i++)
        printColoredChar(pixels[i]);
    printf("\033[1;38;5;8m %d", lineNumber);
    printf("\n");
}
// get random color of the enum

color getRandomColor()
{
    return (color)(rand() % NB_COLORS);
}

void printColumNumber()
{
    printf("\033[51;1;38;5;8m   ");
    for (int i = 1; i <= WIDTH; i++)
    {
        if (i < 10)
            printf(" ");
        printf("%d", i);
    }
    printf("\n");
}

void printMap(map_t map)
{
    printColumNumber();
    for (int i = 0; i < HEIGHT; i++)
        printLine(map[i], i + 1);
    printColumNumber();
}

void updateMap(map_t map, int x, int y, color newColor)
{
    map[y - 1][x - 1] = newColor;
}

void placePixel(int x, int y, color newColor)
{
    map_t map;
    readMap(map);
    updateMap(map, x, y, newColor);
    exportMap(map);
}

void drawMap()
{
    system("clear");
    map_t map;
    readMap(map);
    printMap(map);
}

void exportMap(map_t map)
{
    FILE *file = fopen(MAP_FILE_NAME, "wb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fwrite(map, sizeof(color), WIDTH * HEIGHT, file);
    fclose(file);
}

void readMap(map_t map)
{
    FILE *file = fopen(MAP_FILE_NAME, "rb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fread(map, sizeof(color), WIDTH * HEIGHT, file);
    fclose(file);
}