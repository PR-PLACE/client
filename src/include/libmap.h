#define WIDTH 50
#define HEIGHT WIDTH
#define NB_COLORS 10

#define MAP_FILE_NAME "../maps/map.bin"

typedef enum
{
    BLEUE = 12,
    ROUGE = 9,
    VERT = 10,
    JAUNE = 11,
    NOIR = 0,
    BLANC = 15,
    MAUVE = 13,
    VIOLET = 5,
    MARRON = 130,
    ORANGE = 214,
} color;

void printMap(color map[HEIGHT][WIDTH]);
void exportMap(color map[HEIGHT][WIDTH]);