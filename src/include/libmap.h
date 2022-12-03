#ifndef INCLUDE_LIBMAP
#define INCLUDE_LIBMAP 1

#define WIDTH 50
#define HEIGHT WIDTH
#define NB_COLORS 10

#define MAP_FILE_NAME "../maps/map.bin"
#define printColoredChar(color) (printf("\033[38;5;%dm██\033[0m", color))


typedef enum
{
    BLUE = 12,
    RED = 9,
    GREEN = 10,
    YELLOW = 11,
    BLACK = 0,
    WHITE = 15,
    LIGHT_PURPLE = 13,
    PURPLE = 5,
    BROWN = 130,
    ORANGE = 214,
} color;

typedef struct pixel_t
{
    int abscissa;
    int ordinate;
    color color;
} pixel_t;

#define COLOR_NUMBER 10

static color colors[COLOR_NUMBER] = {BLUE, RED, GREEN, YELLOW, BLACK, WHITE, LIGHT_PURPLE, PURPLE, BROWN, ORANGE};
typedef color map_t[HEIGHT][WIDTH];

void readMap(map_t *map);
void printMap(map_t *map);
void drawMap(map_t *map);
void placePixel(pixel_t *pixel, map_t map);
void exportMap(map_t map);
int isColor(color color);
#endif
