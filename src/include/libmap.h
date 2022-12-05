#ifndef INCLUDE_LIBMAP
#define INCLUDE_LIBMAP 1

#define WIDTH 100
#define HEIGHT 50
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

/**
 * Function to read the binary file map
 * @param map_t* map : the map we want to fill from the file
 */
void readMap(map_t *map);

/**
 * Function to display the map in the terminal
 * @param map_t* map : the map we want to display
 */
void printMap(map_t *map);

/**
 * Function to draw the map in the terminal (clear before printing)
 * @param map_t* map : the map we want to draw
 */
void drawMap(map_t *map);

/**
 * Function place a pixel in the map
 * @param map_t* map : the map we want to update
 * @param pixel_t* pixel : the pixel we want to place
 */
void placePixel(pixel_t *pixel, map_t map);

/**
 * Function to export the map into the binary file
 * @param map_t*map : the map we want to export
 */
void exportMap(map_t map);

/**
 * Function to know if the color passed in param is in the colors list
 * @param color color : the color we want to check
 * @return int : 1 if the color is in the list, 0 otherwise
 */
int isColor(color color);
#endif
