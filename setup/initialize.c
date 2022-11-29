#include <stdio.h>
#include <stdlib.h>
#include "../lib/libmap.h"

int main(int argc, char const *argv[])
{
    color map[HEIGHT][WIDTH];
    for (int i = 0; i <= HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            map[j][i] = BLANC;
        }
    }
    exportMap(map, "../maps/map.bin");
    return 0;
}
