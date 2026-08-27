#ifndef JOURNEY_MAP_H
#define JOURNEY_MAP_H

#include <stdbool.h>

#define JOURNEY_MAP_WIDTH  64
#define JOURNEY_MAP_HEIGHT 36

typedef enum
{
    JOURNEY_TILE_GRASS = 0,
    JOURNEY_TILE_WATER,
    JOURNEY_TILE_FOREST,
    JOURNEY_TILE_STONE,
    JOURNEY_TILE_GRAVE
} JourneyTileType;

typedef struct
{
    JourneyTileType type;
    bool walkable;
} JourneyTile;

typedef struct
{
    int width;
    int height;
    JourneyTile tiles[JOURNEY_MAP_WIDTH][JOURNEY_MAP_HEIGHT];
} JourneyMap;

void journey_map_init(JourneyMap *map);

const JourneyTile *journey_map_get_tile(
    const JourneyMap *map,
    int x,
    int y
);

bool journey_map_is_walkable(
    const JourneyMap *map,
    int x,
    int y
);

bool journey_map_has_interaction(
    const JourneyMap *map,
    int x,
    int y
);

#endif

