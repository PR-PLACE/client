#define WIDTH 50
#define HEIGHT WIDTH
#define NB_COLORS 10

#define MAP_FILE_NAME "../maps/map.bin"

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

/**
 * Function to read the binary file where the map is stored
 */
void readMap();

/**
 * Export a new map in the binary file
 */
void exportMap(map_t map);

/**
 * Display the map in the terminal
 */
void printMap(map_t map);

/**
 * Clear the terminal, and read the map to display it
 */
void drawMap();

/**
 * Place a pixel in the map and export it
 */
void placePixel(pixel_t pixel);

/**
 * Modify a pixel within the map
 */
void updateMap(map_t map, pixel_t pixel);