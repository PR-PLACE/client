#ifndef INCLUDE_LIBMAP
#define INCLUDE_LIBMAP 1

#define WIDTH 50
#define HEIGHT WIDTH
#define NB_COLORS 10

#define MAP_FILE_NAME "../maps/map.bin"
#define printColoredChar(color) (printf("\033[38;5;%dm██\033[0m", color))

#define printColoredChar(color) (printf("\033[38;5;%dm██\033[0m", color))

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

typedef struct pixel_t
{
    int abscissa;
    int ordinate;
    color color;
} pixel_t;

static color colors[NB_COLORS] = {BLEUE, ROUGE, VERT, JAUNE, NOIR, BLANC, MAUVE, VIOLET, MARRON, ORANGE};
typedef color map_t[HEIGHT][WIDTH];

void readMap(color map[HEIGHT][WIDTH]);
void printMap(color map[HEIGHT][WIDTH]);
void drawMap();
void updateMap(map_t map, pixel_t pixel);
void placePixel(pixel_t pixel);
void exportMap(color map[HEIGHT][WIDTH]);
int isColor(color color);

#endif
